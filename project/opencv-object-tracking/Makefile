OPENCV4_FLAGS = $(shell pkg-config --cflags --libs opencv4)
GRPCPP_FLAGS = $(shell pkg-config --cflags --libs grpc++)
PROTOBUF_FLAGS = $(shell pkg-config --cflags --libs protobuf)
FFMPEG_FLAGS = $(shell pkg-config --cflags --libs libavutil libavcodec libavformat libswscale)

GRPC_CPP_PLUGIN = $(shell which grpc_cpp_plugin)

TARGETS = main server client test_decoder

.PHONY: all
all: $(TARGETS)

main: main.cpp
	g++ $< $(OPENCV4_FLAGS) -O2 -o $@

test_decoder: test_decoder.cpp decoder.hpp
	g++ $< $(OPENCV4_FLAGS) $(FFMPEG_FLAGS) -O2 -o $@

object_tracking.pb.cc:
object_tracking.pb.h: object_tracking.proto
	protoc --cpp_out=. $<

object_tracking.pb.o: object_tracking.pb.cc object_tracking.pb.h
	g++ $< $(GRPCPP_FLAGS) $(PROTOBUF_FLAGS) -O2 -c -o $@

object_tracking.grpc.pb.cc:
object_tracking.grpc.pb.h: object_tracking.proto  object_tracking.pb.h
	protoc --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN) $<

object_tracking.grpc.pb.o: object_tracking.grpc.pb.cc object_tracking.grpc.pb.h
	g++ $< $(GRPCPP_FLAGS) $(PROTOBUF_FLAGS) -O2 -c -o $@

server.o: server.cpp object_tracking.grpc.pb.h decoder.hpp tracker.hpp
	g++ $< $(GRPCPP_FLAGS) $(PROTOBUF_FLAGS) $(OPENCV4_FLAGS) $(FFMPEG_FLAGS) -O2 -c -o $@

server: server.o object_tracking.pb.o object_tracking.grpc.pb.o
	g++ $^ $(GRPCPP_FLAGS) $(PROTOBUF_FLAGS) $(OPENCV4_FLAGS) $(FFMPEG_FLAGS) -lpthread -lgrpc++_reflection -ldl -O2 -o $@

client.o: client.cpp object_tracking.grpc.pb.h decoder.hpp bundle.hpp
	g++ $< $(GRPCPP_FLAGS) $(PROTOBUF_FLAGS) $(OPENCV4_FLAGS) $(FFMPEG_FLAGS) -O2 -c -o $@

client: client.o object_tracking.pb.o object_tracking.grpc.pb.o
	g++ $^ $(GRPCPP_FLAGS) $(PROTOBUF_FLAGS) $(OPENCV4_FLAGS) $(FFMPEG_FLAGS) -lpthread -lgrpc++_reflection -ldl -O2 -o $@

.PHONY: proto
proto: object_tracking.pb.o object_tracking.grpc.pb.o

.PHONY: clean
clean:
	rm -f $(TARGETS) *.pb.h *.pb.cc *.o
