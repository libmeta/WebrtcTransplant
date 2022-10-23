#pragma once

#include "api/video/video_codec_type.h"
#include "common_video/h264/h264_bitstream_parser.h"
#include "common_video/h265/h265_bitstream_parser.h"
#include "rtc_base/synchronization/mutex.h"

#include <mutex>

class XQpParser {
public:
    absl::optional<uint32_t> Parse(webrtc::VideoCodecType codec_type,
                                   const uint8_t *frame_data,
                                   size_t frame_size);
    class H264QpParser {
    public:
        absl::optional<uint32_t> Parse(const uint8_t *frame_data, size_t frame_size);

    private:
        webrtc::Mutex mutex_;
        webrtc::H264BitstreamParser bitstream_parser_ RTC_GUARDED_BY(mutex_);
    };

    class H265QpParser {
    public:
        absl::optional<uint32_t> Parse(const uint8_t *frame_data, size_t frame_size);

    private:
        webrtc::Mutex mutex_;
        webrtc::H265BitstreamParser bitstream_parser_ RTC_GUARDED_BY(mutex_);
    };

    H264QpParser h264_parsers_;
    H265QpParser h265_parsers_;
};
