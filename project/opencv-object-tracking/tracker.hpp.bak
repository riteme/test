#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/dnn.hpp>

enum ObjectType : int {
    OBJECT_CAR = 7,
    OBJECT_HORSE = 13,
    OBJECT_PERSON = 15,
};

constexpr const char *label_map[] = {
    [0] = "background",   [1] = "aeroplane", [2] = "bicycle",    [3] = "bird",
    [4] = "boat",         [5] = "bottle",    [6] = "bus",        [7] = "car",
    [8] = "cat",          [9] = "chair",     [10] = "cow",       [11] = "diningtable",
    [12] = "dog",         [13] = "horse",    [14] = "motorbike", [15] = "person",
    [16] = "pottedplant", [17] = "sheep",    [18] = "sofa",      [19] = "train",
    [20] = "tvmonitor",
};

constexpr struct {
    int width = 300;
    int height = 300;
    float mean = 127.5f;
    float threshold = 0.20f;
} detector_config;

constexpr struct {
    float threshold = 0.91f;
} tracker_config;

struct ObjectTracker {
    struct Tracker {
        cv::Ptr<cv::Tracker> inst;
        cv::Rect bbox;
        bool last_fail;

        Tracker() {
            inst = cv::TrackerDaSiamRPN::create();
        }

        float last_score() const {
            auto ptr = reinterpret_cast<cv::TrackerDaSiamRPN *>(inst.get());
            return ptr->getTrackingScore();
        }

        void init(const cv::Mat &frame, cv::Rect _bbox) {
            bbox = _bbox;
            inst->init(scale_frame(frame), scale_bbox(bbox));
        }

        void update(const cv::Mat &frame) {
            last_fail = !inst->update(scale_frame(frame), bbox);
            if (!last_fail)
                bbox = enlarge_bbox(bbox);
        }

    private:
        cv::Mat scale_frame(const cv::Mat &frame) const {
            cv::Mat scaled_frame;
            cv::resize(frame, scaled_frame, cv::Size(640, 360), 0, 0, cv::INTER_AREA);
            return scaled_frame;
        }

        cv::Rect scale_bbox(const cv::Rect &bbox) const {
            return {bbox.x / 2, bbox.y / 2, bbox.width / 2, bbox.height / 2};
        }

        cv::Rect enlarge_bbox(const cv::Rect &bbox) const {
            return {bbox.x * 2, bbox.y * 2, bbox.width * 2, bbox.height * 2};
        }
    };

    int target_idx;
    Tracker tracker;
    cv::dnn::Net detector;

    ObjectTracker(int _target_idx) :
        target_idx(_target_idx)
    {
        detector = cv::dnn::readNetFromCaffe(
            "mobilenet.prototxt",
            "mobilenet.caffemodel"
        );
        assert(!detector.empty());
    }

    void detect(const cv::Mat &frame) {
        if (!tracker.last_fail && tracker.last_score() >= tracker_config.threshold)
            return;

        auto size = cv::Size(detector_config.width, detector_config.height);
        cv::Mat scaled_frame;
        cv::resize(frame, scaled_frame, size, 0, 0, cv::INTER_AREA);
        auto input = cv::dnn::blobFromImage(
            scaled_frame,
            1.0f / detector_config.mean,
            size,
            cv::Scalar(detector_config.mean, detector_config.mean, detector_config.mean)
        );
        detector.setInput(input);
        auto detection = detector.forward();
        auto result = cv::Mat(
            detection.size[2],
            detection.size[3],
            CV_32F,
            detection.ptr<float>()
        );

        struct Item {
            float confidence;
            cv::Rect bbox;

            bool operator<(const Item &rhs) const {
                return confidence < rhs.confidence;
            }
        };

        std::vector<Item> items;
        for (int i = 0; i < result.rows; i++) {
            float confidence = result.at<float>(i, 2);
            if (confidence < detector_config.threshold)
                continue;

            int idx = (int)result.at<float>(i, 1);
            if (idx != target_idx)
                continue;

            float x = result.at<float>(i, 3) * frame.cols;
            float y = result.at<float>(i, 4) * frame.rows;
            float w = result.at<float>(i, 5) * frame.cols - x;
            float h = result.at<float>(i, 6) * frame.rows - y;
            items.push_back({confidence, {(int)x, (int)y, (int)w, (int)h}});
        }

        if (items.empty())
            return;

        auto item = std::max_element(items.begin(), items.end());
        tracker.init(frame, item->bbox);
        printf(
            "new {x=%d, y=%d, w=%d, h=%d}\n",
            item->bbox.x,
            item->bbox.y,
            item->bbox.width,
            item->bbox.height
        );
    }

    void update(const cv::Mat &frame) {
        tracker.update(frame);
    }
};
