#pragma once

/**
 * Decode a video file (in memory buffer) into frames (in cv::Mat)
 */

#include <string>

#include <opencv2/opencv.hpp>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class Decoder {
public:
    Decoder(const std::string &_data) :
        data(_data),
        data_ptr(data.data()),
        data_remain(data.size())
    {
        avio_ctx_buf = (uint8_t *)av_malloc(avio_ctx_buf_size);
        if (!avio_ctx_buf)
            throw std::runtime_error("av_malloc: avio_ctx_buf");

        avio_ctx = avio_alloc_context(
            avio_ctx_buf,
            avio_ctx_buf_size,
            0,
            this,
            _read_packet,
            NULL,
            NULL
        );
        if (!avio_ctx)
            throw std::runtime_error("avio_alloc_context");

        fmt_ctx = avformat_alloc_context();
        if (!fmt_ctx)
            throw std::runtime_error("avformat_alloc_context");
        fmt_ctx->pb = avio_ctx;
        if (avformat_open_input(&fmt_ctx, NULL, NULL, NULL) < 0)
            throw std::runtime_error("avformat_open_input");
        if (avformat_find_stream_info(fmt_ctx, NULL) < 0)
            throw std::runtime_error("avformat_find_stream_info");

        bool found = false;
        for (int i = 0; i < fmt_ctx->nb_streams; i++) {
            stream = fmt_ctx->streams[i];
            codec_param = stream->codecpar;
            if (codec_param->codec_type == AVMEDIA_TYPE_VIDEO) {
                found = true;
                break;
            }
        }
        if (!found)
            throw std::runtime_error("find video stream");

        codec = avcodec_find_decoder(codec_param->codec_id);
        if (!codec)
            throw std::runtime_error("avcodec_find_decoder");

        codec_ctx = avcodec_alloc_context3(codec);
        if (!codec_ctx)
            throw std::runtime_error("avcodec_alloc_context3");
        if (avcodec_parameters_to_context(codec_ctx, codec_param) < 0)
            throw std::runtime_error("avcodec_parameters_to_context");
        if (avcodec_open2(codec_ctx, codec, NULL) < 0)
            throw std::runtime_error("avcodec_open2");

        packet = av_packet_alloc();
        if (!packet)
            throw std::runtime_error("av_packet_alloc");

        frame = av_frame_alloc();
        if (!frame)
            throw std::runtime_error("av_frame_alloc");

        sws_ctx = sws_getContext(
            codec_ctx->width,
            codec_ctx->height,
            codec_ctx->pix_fmt,
            codec_ctx->width,
            codec_ctx->height,
            AV_PIX_FMT_BGR24,
            SWS_BICUBIC,
            NULL,
            NULL,
            NULL
        );
        if (!sws_ctx)
            throw std::runtime_error("sws_getContext");

        bgr_frame = av_frame_alloc();
        if (!bgr_frame)
            throw std::runtime_error("av_frame_alloc");
        bgr_frame->format = AV_PIX_FMT_BGR24;
        bgr_frame->width = codec_ctx->width;
        bgr_frame->height = codec_ctx->height;
        if (av_frame_get_buffer(bgr_frame, 0) < 0)
            throw std::runtime_error("av_frame_get_buffer");
    }

    ~Decoder() {
        av_frame_free(&bgr_frame);
        sws_freeContext(sws_ctx);
        av_frame_free(&frame);
        av_packet_free(&packet);
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&fmt_ctx);
        av_freep(&avio_ctx->buffer);
        avio_context_free(&avio_ctx);
    }

    bool read(cv::Mat &out_frame) {
        while (true) {
            if (need_unref) {
                av_packet_unref(packet);
                need_unref = false;
            }

            if (need_read) {
                if (av_read_frame(fmt_ctx, packet) < 0)
                    return false;
                if (avcodec_send_packet(codec_ctx, packet) < 0)
                    throw std::runtime_error("avcodec_send_packet");
                need_read = false;
                need_unref = true;
            }

            int ret = avcodec_receive_frame(codec_ctx, frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                need_read = true;
                continue;
            }
            if (ret < 0)
                throw std::runtime_error("avcodec_receive_frame");

            break;
        }

        if (sws_scale_frame(sws_ctx, bgr_frame, frame) < 0)
            throw std::runtime_error("sws_scale_frame");

        out_frame = cv::Mat(
            bgr_frame->height,
            bgr_frame->width,
            CV_8UC3,
            bgr_frame->data[0],
            bgr_frame->linesize[0]
        );

        return true;
    }

    ssize_t num_frames() const {
        return stream->nb_frames;
    }

    AVRational fps() const {
        return stream->r_frame_rate;
    }

private:
    static constexpr int avio_ctx_buf_size = 4096;

    const std::string &data;
    const char *data_ptr;
    size_t data_remain;

    uint8_t *avio_ctx_buf;
    AVIOContext *avio_ctx;
    AVFormatContext *fmt_ctx;
    AVStream *stream;
    AVCodecParameters *codec_param;
    const AVCodec *codec;
    AVCodecContext *codec_ctx;
    AVPacket *packet;
    AVFrame *frame;
    SwsContext *sws_ctx;
    AVFrame *bgr_frame;
    bool need_read = true;
    bool need_unref = false;

    static int _read_packet(void *opaque, uint8_t *buf, int buf_size) {
        auto self = reinterpret_cast<Decoder *>(opaque);
        auto size = self->read_packet(buf, buf_size);
        return size == 0 ? AVERROR_EOF : size;
    }

    size_t read_packet(uint8_t *buf, size_t buf_size) {
        if (buf_size > data_remain)
            buf_size = data_remain;
        memcpy(buf, data_ptr, buf_size);
        data_ptr += buf_size;
        data_remain -= buf_size;
        return buf_size;
    }
};
