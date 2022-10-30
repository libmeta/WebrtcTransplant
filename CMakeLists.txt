cmake_minimum_required(VERSION 3.22)

project(qp_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(abseil-cpp)

add_definitions(-DWEBRTC_LINUX=1)
add_definitions(-DWEBRTC_POSIX=1)
add_definitions(-DVIDEO_DIR_PATH="${CMAKE_SOURCE_DIR}/video")

file(GLOB_RECURSE WEBRTC_SOURCES0   ${CMAKE_SOURCE_DIR}/webrtc/*.cc)
file(GLOB_RECURSE WEBRTC_SOURCES1   ${CMAKE_SOURCE_DIR}/webrtc/*/*.cc)
file(GLOB_RECURSE WEBRTC_SOURCES2   ${CMAKE_SOURCE_DIR}/webrtc/*/*/*.cc)
set(WEBRTC_SOURCES ${WEBRTC_SOURCES0} ${WEBRTC_SOURCES1} ${WEBRTC_SOURCES2})

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/webrtc
    ${CMAKE_SOURCE_DIR}/webrtc/common_video/h264
    ${CMAKE_SOURCE_DIR}/webrtc/common_video/h265
)

add_executable(qp_parser
    main.cpp
    qp_parser.cpp
    ${WEBRTC_SOURCES}
)

target_link_libraries(qp_parser absl::base absl::synchronization absl::strings absl::algorithm absl::numeric)

install(TARGETS qp_parser
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
