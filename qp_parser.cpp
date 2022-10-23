#include "qp_parser.h"

#include <mutex>
#include <utility>

//#include "api/array_view.h"

absl::optional<uint32_t> XQpParser::Parse(webrtc::VideoCodecType codec_type,
                                          const uint8_t *frame_data,
                                          size_t frame_size)
{
    if (frame_data == nullptr || frame_size == 0) {
        return absl::nullopt;
    }

    if (codec_type == webrtc::VideoCodecType::kVideoCodecVP8) {
        return -1;
    } else if (codec_type == webrtc::VideoCodecType::kVideoCodecVP9) {
        return -1;
    } else if (codec_type == webrtc::VideoCodecType::kVideoCodecH264) {
        return h264_parsers_.Parse(frame_data, frame_size);
    } else if (codec_type == webrtc::VideoCodecType::kVideoCodecH265) {
        return h265_parsers_.Parse(frame_data, frame_size);
    }

    return absl::nullopt;
}

absl::optional<uint32_t> XQpParser::H264QpParser::Parse(const uint8_t *frame_data, size_t frame_size)
{
    webrtc::MutexLock lock(&mutex_);
    bitstream_parser_.ParseBitstream(rtc::ArrayView<const uint8_t>(frame_data, frame_size));
    return bitstream_parser_.GetLastSliceQp();
}

absl::optional<uint32_t> XQpParser::H265QpParser::Parse(const uint8_t *frame_data, size_t frame_size)
{
    webrtc::MutexLock lock(&mutex_);
    bitstream_parser_.ParseBitstream(rtc::ArrayView<const uint8_t>(frame_data, frame_size));
    return bitstream_parser_.GetLastSliceQp();
}
