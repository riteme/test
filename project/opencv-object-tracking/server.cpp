#include "decoder.hpp"
#include "tracker.hpp"

#include <grpcpp/grpcpp.h>
#include "object_tracking.grpc.pb.h"

class ObjectTrackingImpl final : public ObjectTracking::Service {
public:
    grpc::Status process(
        grpc::ServerContext *ctx,
        grpc::ServerReaderWriter<VideoFrame, VideoChunk> *stream
    ) override {
        puts("Hello!");

        VideoChunk chunk;
        cv::Mat frame;
        ObjectTracker tracker(OBJECT_CAR);

        uint64_t global_index = 0;
        while (stream->Read(&chunk)) {
            auto decoder = Decoder(chunk.data());
            auto fps = decoder.fps();
            printf("duration=%lu us, fps=%d/%d\n", chunk.duration_us(), fps.num, fps.den);

            uint64_t local_index = 0;
            while (decoder.read(frame)) {
                if (local_index == 0)
                    tracker.detect(frame);
                else
                    tracker.update(frame);

                VideoFrame result;
                result.set_chunk_finished(false);
                result.set_index_in_stream(global_index++);
                result.set_index_in_chunk(local_index++);
                result.set_found(!tracker.tracker.last_fail);
                result.set_score(tracker.tracker.last_score());

                auto bbox = tracker.tracker.bbox;
                auto dest = result.mutable_bbox();
                dest->set_x(bbox.x);
                dest->set_y(bbox.y);
                dest->set_width(bbox.width);
                dest->set_height(bbox.height);

                stream->Write(result);
            }

            VideoFrame end;
            end.set_chunk_finished(true);
            end.set_index_in_stream(global_index);
            end.set_index_in_chunk(local_index);
            stream->Write(end);
        }

        puts("Finished");
        return grpc::Status::OK;
    }
};

int main() {
    ObjectTrackingImpl service;
    grpc::ServerBuilder builder;
    builder.SetMaxMessageSize(128 * 1024 * 1024);  // 128 MiB
    builder.AddListeningPort("0.0.0.0:23324", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    auto server = builder.BuildAndStart();
    server->Wait();
    return 0;
}
