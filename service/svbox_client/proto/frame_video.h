#ifndef FRAME_VIDEO_H_____
#define FRAME_VIDEO_H_____
#include <stdint.h>
#define FORMAT_UYVY 1
#define FORMAT_YUYV 2

struct FrameHeader {
  int8_t camera;
  int8_t format;
  uint16_t sequence;
  uint16_t width;
  uint16_t height;
  uint16_t exposure; // time for exposure, unit 10us, max 655.36ms
  uint64_t timestamp;
} __attribute__((packed));
#define UDP_SRC_PORT 15934
#endif