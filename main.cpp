#include <iostream>
#include <vector>

#include "qp_parser.h"

int main() {
    std::cout << "videos Path : " << VIDEO_DIR_PATH << std::endl;
    FILE *testH264 = ::fopen(VIDEO_DIR_PATH "/601.264","rb");
    FILE *testH265 = ::fopen(VIDEO_DIR_PATH "/akiyo.x265.qp_30.265","rb");

    std::vector<uint8_t> buffer(1024,0);
    XQpParser qPParser;

    std::cout << "h264 qp array:";
    while(true){
        auto ret = fread(buffer.data(),1,buffer.size(),testH264);
        if(ret <=0){
            std::cout << std::endl << std::endl;
            break;
        }

        auto qp = qPParser.Parse(webrtc::VideoCodecType::kVideoCodecH264,buffer.data(),ret);
        if(qp.has_value()){
            std::cout << qp.value_or(UINT8_MAX) << " ";
        }
    }

    std::cout << "h265 qp array:";
    while(true){
        auto ret = fread(buffer.data(),1,buffer.size(),testH265);
        if(ret <=0 ){
            std::cout << std::endl;
            break;
        }

        auto qp = qPParser.Parse(webrtc::VideoCodecType::kVideoCodecH265,buffer.data(),ret);
        if(qp.has_value()){
            std::cout << qp.value_or(UINT8_MAX) << " ";
        }
    }

    fclose(testH264);
    fclose(testH265);

    return 0;
}
