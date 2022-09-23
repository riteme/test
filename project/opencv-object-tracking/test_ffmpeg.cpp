#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Use OpenCV for showing the inage
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

#define INBUF_SIZE 1024

//static void pgm_save(unsigned char* buf, int wrap, int xsize, int ysize, char* filename)
//{
//    FILE* f;
//    int i;
//
//    f = fopen(filename, "wb");
//    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
//    for (i = 0; i < ysize; i++)
//        fwrite(buf + i * wrap, 1, xsize, f);
//    fclose(f);
//}


//Save RGB image as PPM file format
//static void ppm_save(unsigned char* buf, int wrap, int xsize, int ysize, char* filename)
//{
//    FILE* f;
//    int i;
//
//    f = fopen(filename, "wb");
//    fprintf(f, "P6\n%d %d\n%d\n", xsize, ysize, 255);
//
//    for (i = 0; i < ysize; i++)
//    {
//        fwrite(buf + i * wrap, 1, xsize*3, f);
//    }
//
//    fclose(f);
//}


static void decode(AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt, const char* filename)
{
    struct SwsContext* sws_ctx = NULL;
    char filename_buf[1024];
    int ret;
    int sts;

    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0)
    {
        fprintf(stderr, "Error sending a packet for decoding\n");
        exit(1);
    }

    //Create SWS Context for converting from decode pixel format (like YUV420) to BGR
    ////////////////////////////////////////////////////////////////////////////
    sws_ctx = sws_getContext(dec_ctx->width,
                             dec_ctx->height,
                             dec_ctx->pix_fmt,
                             dec_ctx->width,
                             dec_ctx->height,
                             AV_PIX_FMT_BGR24, //For OpenCV, we want BGR pixel format.
                             SWS_BICUBIC,
                             NULL,
                             NULL,
                             NULL);

    if (sws_ctx == nullptr)
    {
        return;  //Error!
    }
    ////////////////////////////////////////////////////////////////////////////


    //Allocate frame for storing image converted to RGB.
    ////////////////////////////////////////////////////////////////////////////
    AVFrame* pBGRFrame = av_frame_alloc();

    pBGRFrame->format = AV_PIX_FMT_BGR24;
    pBGRFrame->width = dec_ctx->width;
    pBGRFrame->height = dec_ctx->height;

    sts = av_frame_get_buffer(pBGRFrame, 0);

    if (sts < 0)
    {
        return;  //Error!
    }
    ////////////////////////////////////////////////////////////////////////////


    while (ret >= 0)
    {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            return;
        }
        else if (ret < 0)
        {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }

        printf("saving frame %3d\n", dec_ctx->frame_number);
        fflush(stdout);

        /* the picture is allocated by the decoder. no need to
           free it */
        //snprintf(buf, sizeof(buf), "%s_%03d.pgm", filename, dec_ctx->frame_number);
        //pgm_save(frame->data[0], frame->linesize[0],
        //    frame->width, frame->height, buf);

        //Convert from input format (e.g YUV420) to BGR:
        ////////////////////////////////////////////////////////////////////////////
        sts = sws_scale(sws_ctx,                //struct SwsContext* c,
                        frame->data,            //const uint8_t* const srcSlice[],
                        frame->linesize,        //const int srcStride[],
                        0,                      //int srcSliceY,
                        frame->height,          //int srcSliceH,
                        pBGRFrame->data,        //uint8_t* const dst[],
                        pBGRFrame->linesize);   //const int dstStride[]);

        if (sts != frame->height)
        {
            return;  //Error!
        }

        snprintf(filename_buf, sizeof(filename_buf), "%s_%03d.jpg", filename, dec_ctx->frame_number);
        //ppm_save(pBGRFrame->data[0], pBGRFrame->linesize[0], pBGRFrame->width, pBGRFrame->height, buf);
        ////////////////////////////////////////////////////////////////////////////

        //Use OpenCV for showing the image (and save the image in JPEG format):
        ////////////////////////////////////////////////////////////////////////////
        cv::Mat img = cv::Mat(pBGRFrame->height, pBGRFrame->width, CV_8UC3, pBGRFrame->data[0], pBGRFrame->linesize[0]);    //cv::Mat is OpenCV "thin image wrapper".
        cv::imshow("img", img);
        cv::waitKey(100);   //Wait 100msec (relativly long time - for testing).

        //Save the inage in JPEG format using OpenCV
        cv::imwrite(filename_buf, img);
        ////////////////////////////////////////////////////////////////////////////

    }

    //Free
    sws_freeContext(sws_ctx);
    av_frame_free(&pBGRFrame);
}

int main(int argc, char** argv)
{
    const char* filename, * outfilename;
    const AVCodec* codec;
    AVCodecParserContext* parser;
    AVCodecContext* c = NULL;
    FILE* f;
    AVFrame* frame;
    uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    uint8_t* data;
    size_t   data_size;
    int ret;
    AVPacket* pkt;

    filename = argv[1];
    outfilename = argv[2];

    pkt = av_packet_alloc();
    if (!pkt)
    {
        exit(1);
    }

    //memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    memset(inbuf, 0, sizeof(inbuf));

    codec = avcodec_find_decoder(AV_CODEC_ID_HEVC);
    if (!codec)
    {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }

    parser = av_parser_init(codec->id);
    if (!parser)
    {
        fprintf(stderr, "parser not found\n");
        exit(1);
    }

    c = avcodec_alloc_context3(codec);
    if (!c)
    {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    if (avcodec_open2(c, codec, NULL) < 0)
    {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }

    f = fopen(filename, "rb");
    if (!f)
    {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }

    frame = av_frame_alloc();
    if (!frame)
    {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }

    while (!feof(f))
    {
        /* read raw data from the input file */
        data_size = fread(inbuf, 1, INBUF_SIZE, f);

        if (!data_size)
        {
            break;
        }

        /* use the parser to split the data into frames */
        data = inbuf;
        while (data_size > 0)
        {
            ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size, data, (int)data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);

            if (ret < 0)
            {
                fprintf(stderr, "Error while parsing\n");
                exit(1);
            }

            data += ret;
            data_size -= ret;


            if (pkt->data)
            {
                printf("NICE\n");
                decode(c, frame, pkt, outfilename);
            }
        }
    }

    /* flush the decoder */
    decode(c, frame, NULL, outfilename);

    fclose(f);

    av_parser_close(parser);
    avcodec_free_context(&c);
    av_frame_free(&frame);
    av_packet_free(&pkt);

    return 0;
}
