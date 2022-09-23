## Prerequisites

- OpenCV 4.6.0
- vtk 9.1.0

## Models

### MobileNet

<https://github.com/djmv/MobilNet_SSD_opencv>

<https://gist.github.com/yiling-chen/7d36389192d54f89a5fe0b810ac7bdf3>

### DaSiamRPN

From <https://gitcode.net/greenplum/opencv/-/blob/next/samples/dnn/dasiamrpn_tracker.cpp>:

> DaSiamRPN tracker.
>
> Original paper: <https://arxiv.org/abs/1808.06048>
>
> Link to original repo: <https://github.com/foolwood/DaSiamRPN>
>
> Links to onnx models:
>
> - network:     <https://www.dropbox.com/s/rr1lk9355vzolqv/dasiamrpn_model.onnx?dl=0>
> - kernel_r1:   <https://www.dropbox.com/s/999cqx5zrfi7w4p/dasiamrpn_kernel_r1.onnx?dl=0>
> - kernel_cls1: <https://www.dropbox.com/s/qvmtszx5h339a0w/dasiamrpn_kernel_cls1.onnx?dl=0>

### YOLOv3

<https://pyimagesearch.com/2018/11/12/yolo-object-detection-with-opencv/>
<https://pjreddie.com/darknet/yolo/>

- yolov3-spp.cfg: <https://github.com/pjreddie/darknet/blob/master/cfg/yolov3-spp.cfg>
- yolov3-spp.weights: <https://pjreddie.com/media/files/yolov3-spp.weights>

## Datasets

### GOT-10k

GOT-10k: Generic Object Tracking Benchmark

<http://got-10k.aitestunion.com/index>

## Issues

### Split Video

<https://blog.programster.org/ffmpeg-split-video-into-chunks>

```
ffmpeg \
    -i input.mkv \
    -c copy \
    -map 0 \
    -segment_time 00:20:00 \
    -f segment \
    -reset_timestamps 1 \
    output%03d.mkv
```

### MP4 Partial File

```
ffmpeg stream 1, offset 0x2c: partial file
```

<https://stackoverflow.com/questions/62946707/ffprobe-reports-some-wrong-meta-data-but-only-when-input-is-piped-in>

### HLS Streaming

<https://www.dacast.com/blog/hls-streaming-protocol/#technical_overview_of_hls_streaming>
<https://developer.apple.com/documentation/http_live_streaming/enabling_low-latency_http_live_streaming_hls>
