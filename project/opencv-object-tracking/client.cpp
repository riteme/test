#include <chrono>

#include "decoder.hpp"
#include "bundle.hpp"
#include "CLI/CLI.hpp"

#include <grpcpp/grpcpp.h>
#include "object_tracking.grpc.pb.h"

using Clock = std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
    std::string bundle_path;
    bool show_visualization = false;

    CLI::App app;
    app.add_option("-i,--input", bundle_path)
        ->required()
        ->check(CLI::ExistingFile);
    app.add_flag("-v,--visual", show_visualization);
    CLI11_PARSE(app, argc, argv);

    auto channel = grpc::CreateChannel("0.0.0.0:23324", grpc::InsecureChannelCredentials());
    auto stub = ObjectTracking::NewStub(channel);

    grpc::ClientContext ctx;
    auto stream = stub->process(&ctx);

    Bundle bundle(bundle_path);
    VideoFrame frame;
    while (true) {
        uint64_t duration_us;
        VideoChunk chunk;
        if (!bundle.read_blob(duration_us, *chunk.mutable_data()))
            break;

        Decoder *decoder = NULL;
        if (show_visualization)
            decoder = new Decoder(chunk.data());

        printf("size=%lu, duration=%lu us\n", chunk.data().size(), duration_us);

        auto begin_tp = Clock::now();
        chunk.set_duration_us(duration_us);
        stream->Write(chunk);

        VideoFrame frame;
        while (stream->Read(&frame) && !frame.chunk_finished()) {
            auto bbox = frame.bbox();
            printf(
                "#%ld-%ld {x=%u, y=%u, w=%u, h=%u} %s %.3f\n",
                frame.index_in_stream(),
                frame.index_in_chunk(),
                bbox.x(),
                bbox.y(),
                bbox.width(),
                bbox.height(),
                frame.found() ? "found" : "",
                frame.score()
            );

            if (show_visualization) {
                cv::Mat cv_frame;
                assert(decoder);
                assert(decoder->read(cv_frame));

                if (frame.found()) {
                    cv::rectangle(
                        cv_frame,
                        cv::Rect(
                            bbox.x(),
                            bbox.y(),
                            bbox.width(),
                            bbox.height()
                        ),
                        cv::Scalar(255, 0, 0),
                        2
                    );

                    auto score_label = std::to_string(frame.score());
                    cv::putText(
                        cv_frame,
                        score_label,
                        cv::Point(bbox.x(), bbox.y()),
                        cv::FONT_HERSHEY_SIMPLEX,
                        1,
                        cv::Scalar(255, 0, 0)
                    );
                }

                cv::imshow("Show", cv_frame);
                cv::waitKey(1);
            }
        }

        auto end_tp = Clock::now();
        auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_tp - begin_tp).count();
        double fps = (double)frame.index_in_chunk() * 1e9 / duration_ns;
        printf("duration=%lu ns, fps=%.3lf\n", duration_ns, fps);
    }

    stream->WritesDone();

    auto status = stream->Finish();
    if (!status.ok()) {
        printf("Error %d: %s\n", status.error_code(), status.error_message().c_str());
        puts(status.error_details().c_str());
    }

    return 0;
}
