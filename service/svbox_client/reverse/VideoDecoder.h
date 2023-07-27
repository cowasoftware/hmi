#pragma once

#include <functional>
#include <QString>
#include <QImage>
#include <QVideoFrame>
#include "iostream"
#include "svbox.pb.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
}

using DecodeCall = std::function<void(QVideoFrame& frame)>;
class VideoDecoder
{
public:
    VideoDecoder();
    virtual ~VideoDecoder();
public:
    // 从url打开流，并初始化参数
    int open(QString url,DecodeCall call);
    // 初始化Decoder参数
    int initDecoder(DecodeCall call);
    int decode2();
    int decodeMediaData(const std::string &data);
    // decode h264
    int decodeH264(svbox::ImageFrame msg);
    int close();

public:
    int width();
    int height();
    int lineSize();
    QVideoFrame::PixelFormat format();
private:
    AVPicture m_Picture;
    AVFormatContext* m_pFormatCtx = nullptr;
    AVCodecContext* m_pCodecCtx = nullptr;
    AVFrame* m_pFrame = nullptr; 
    SwsContext* m_pSwsContext = nullptr;
    AVPacket m_Packet;
    AVFrame* m_pconFrame = nullptr;
    int m_nVideoStreamIndex = -1;

    int m_nVideoWidth = 0;
    int m_nVideoHeight = 0;
    bool m_opened = false;
    DecodeCall m_call;

};

