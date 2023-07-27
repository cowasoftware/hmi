#include "VideoDecoder.h"
#include <QDebug>
#include <QImage>
#include <QDateTime>
#include "ConfigConstants.h"

VideoDecoder::VideoDecoder()
{

}

VideoDecoder::~VideoDecoder()
{
}

int VideoDecoder::open(QString url,DecodeCall call)
{
    int error = 0;

    if (m_opened) {
        error = 0;
        return error;
    }

    AVDictionary* avdic = NULL;
    av_dict_set(&avdic, "rtsp_transport", "tcp", 1);
    av_dict_set(&avdic, "muxdelay", "0", 0);
    //av_dict_set(&avdic, "fflags", "nobuffer", 0);
    av_dict_set(&avdic, "tune", "zerolatency", 0);
    av_dict_set(&avdic, "max_delay", "0", 0);
    //av_dict_set(&avdic, "buffer_size", "1024000", 0);
    //av_dict_set(&avdic, "analyzeduration", "1000000", 0);
    // av_dict_set(&avdic, "stimeout", "3000000", 0);

    m_pFormatCtx = avformat_alloc_context();
    if (0 > (error = avformat_open_input(&m_pFormatCtx, url.toStdString().c_str(), NULL, &avdic)))
    {
        qDebug() << "avformat_open_input failed(): " << error;
        avformat_free_context(m_pFormatCtx);
        m_pFormatCtx = nullptr;
        return -1;
    }

    if (0 > (error = avformat_find_stream_info(m_pFormatCtx, NULL)))
    {
        qDebug() << "avformat_find_stream_info failed(): " << error;
        avformat_free_context(m_pFormatCtx);
        m_pFormatCtx = nullptr;
        return -1;
    }

    m_nVideoStreamIndex = -1;
    for (uint i = 0; i < m_pFormatCtx->nb_streams; i++)
    {
        if (AVMEDIA_TYPE_VIDEO == m_pFormatCtx->streams[i]->codecpar->codec_type)
        {
            m_nVideoStreamIndex = i;
            break;
        }
    }

    if (-1 ==  m_nVideoStreamIndex)
    {
        qDebug() << "Video strema not found";
        avformat_free_context(m_pFormatCtx);
        m_pFormatCtx = nullptr;
        return -1;
    }


    AVCodecID nCodecId = m_pFormatCtx->streams[m_nVideoStreamIndex]->codecpar->codec_id;
    AVCodec* pAVCodec = NULL;

    if (nullptr == (pAVCodec = avcodec_find_decoder(nCodecId)))
    {
        qDebug() << "Codec not found";
        avformat_free_context(m_pFormatCtx);
        m_pFormatCtx = nullptr;
        return -1;
    }

    m_pCodecCtx = avcodec_alloc_context3(pAVCodec);
    if (nullptr == m_pCodecCtx) {
        qDebug() << "avcodec_alloc_context3() failed ";
        avformat_free_context(m_pFormatCtx);
        m_pFormatCtx = nullptr;
        return -1;
    }

    avcodec_parameters_to_context(m_pCodecCtx, m_pFormatCtx->streams[m_nVideoStreamIndex]->codecpar);
    m_nVideoWidth = m_pCodecCtx->width;
    m_nVideoHeight = m_pCodecCtx->height;
    m_pCodecCtx->bit_rate = 0;
    m_pCodecCtx->time_base.num = 1;
    m_pCodecCtx->time_base.den = 20;
    m_pCodecCtx->frame_number = 1;


    if (0 > (error = avcodec_open2(m_pCodecCtx, pAVCodec, NULL)))
    {
        avformat_free_context(m_pFormatCtx);
        avcodec_free_context(&m_pCodecCtx);
        m_pFormatCtx = nullptr;
        return -1;
    }

    m_pFrame = av_frame_alloc();
    m_pconFrame = av_frame_alloc();
    av_image_alloc(m_pconFrame->data, m_pconFrame->linesize, m_nVideoWidth, m_nVideoHeight, AV_PIX_FMT_RGB32, 1);
    m_pSwsContext = sws_getContext(m_nVideoWidth, m_nVideoHeight, AV_PIX_FMT_YUV420P,
        m_nVideoWidth, m_nVideoHeight, AV_PIX_FMT_RGB32,
        SWS_BICUBIC, 0, 0, 0);

    if (nullptr == m_pSwsContext) {
        qDebug() << "sws_getContext() failed";
        av_frame_free(&m_pFrame);
        av_frame_free(&m_pconFrame);
        sws_freeContext(m_pSwsContext);
        avcodec_free_context(&m_pCodecCtx);
        avformat_free_context(m_pFormatCtx);
        m_pSwsContext = nullptr;
        return -1;
    }

    m_call = call;
    return 0;
}

int VideoDecoder::initDecoder(DecodeCall call) {
    int error = 0;
    qDebug() << "******** init decoder...*********" << error;
    if (m_opened) {
        error = 0;
        return error;
    }
    AVCodecID nCodecId = AV_CODEC_ID_H264;
    AVCodec* pAVCodec = NULL;
    if (nullptr == (pAVCodec = avcodec_find_decoder(nCodecId)))
    {
        qDebug() << "Codec not found";
        return -1;
    }

    m_pCodecCtx = avcodec_alloc_context3(pAVCodec);
    if (nullptr == m_pCodecCtx) {
        qDebug() << "avcodec_alloc_context3() failed ";
        return -1;
    }

    m_pCodecCtx->width = 1280;
    m_pCodecCtx->height = 800;
    m_nVideoWidth = m_pCodecCtx->width;
    m_nVideoHeight = m_pCodecCtx->height;
    m_pCodecCtx->bit_rate = 0;
    m_pCodecCtx->time_base.num = 1;
    m_pCodecCtx->time_base.den = 20;
    m_pCodecCtx->frame_number = 1;
    m_pCodecCtx->codec_id = nCodecId;
    m_pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    m_pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;

    if (0 > (error = avcodec_open2(m_pCodecCtx, pAVCodec, NULL)))
    {
        avcodec_free_context(&m_pCodecCtx);
        return -1;
    }

    m_pFrame = av_frame_alloc();
    m_pconFrame = av_frame_alloc();
    av_image_alloc(m_pconFrame->data, m_pconFrame->linesize, m_nVideoWidth, m_nVideoHeight, AV_PIX_FMT_RGB32, 1);
    m_pSwsContext = sws_getContext(m_nVideoWidth, m_nVideoHeight, AV_PIX_FMT_YUV420P,
        m_nVideoWidth, m_nVideoHeight, AV_PIX_FMT_RGB32,
        SWS_BICUBIC, 0, 0, 0);
    
    if (nullptr == m_pSwsContext) {
        qDebug() << "sws_getContext() failed";
        av_frame_free(&m_pFrame);
        av_frame_free(&m_pconFrame);
        sws_freeContext(m_pSwsContext);
        avcodec_free_context(&m_pCodecCtx);
        m_pSwsContext = nullptr;
        return -1;
    }

    m_call = call;
    return 0;
}

int VideoDecoder::decode2()
{
    int ret = 0;
    qDebug() << "***************decode2()****************";

    do {
        if ((ret = av_read_frame(m_pFormatCtx, &m_Packet)) < 0)
        {
            qDebug() << "av_read_frame error, exit... ";
            break;
        }
            

        if (m_Packet.stream_index == m_nVideoStreamIndex) {
            ret = avcodec_send_packet(m_pCodecCtx, &m_Packet);
            if (ret < 0) {
               qDebug() <<  "Error while sending a packet to the decoder";
                ret = -1;
                break;
            }

            while (ret >= 0) {
                ret = avcodec_receive_frame(m_pCodecCtx, m_pFrame);
                if (ret == AVERROR(EAGAIN)) {
                    ret = 0;
                    break;
                }
                else if (ret == AVERROR_EOF) {
                    ret = -1;
                    break;
                }
                else if (ret < 0) {
                    qDebug() << "Error while receiving a frame from the decoder";
                    ret = -1;
                    goto end;
                }
                qDebug() << "decode a frame to show....";
                sws_scale(m_pSwsContext, (const uint8_t* const*)m_pFrame->data, m_pFrame->linesize, 0, m_nVideoHeight, m_pconFrame->data, m_pconFrame->linesize);
                QImage img(m_pconFrame->data[0], m_nVideoWidth, m_nVideoHeight, QImage::Format_RGB32);
                QVideoFrame frame(img);
                if (m_call) {
                    m_call(frame);
                }
            }
        }
        av_packet_unref(&m_Packet);
    } while (false);
end:
    return ret;
}

int VideoDecoder::decodeMediaData(const std::string &data) {
    int ret = 0;
    qDebug() << "***************  start decode media data......****************";
    if(data.empty()) {
        std::cout << "******* data is empty!!!" <<std::endl;
        return -1;
    }
    svbox::ImageFrame msg;
    if(!msg.ParseFromString(data)) {
        qDebug() << "******* parse data failed!!!!";
        return -1;
    }
    if(!msg.has_data()) {
        qDebug() << "******* camera data is empty!!!!";
        return -1;
    }
    uint64_t len = msg.data().size();
    if(msg.has_encode()) {
        if(msg.encode().compare(IMAGE_FRAME_ENCODE_JPEG) == 0) {
            // 解码jpeg
            do {
                qDebug() << "decode a frame to show, encode is jpeg....";
                // sws_scale(m_pSwsContext, (const uint8_t* const*)m_pFrame->data, m_pFrame->linesize, 0, m_nVideoHeight, m_pconFrame->data, m_pconFrame->linesize);
                // const uchar* imgBuf = reinterpret_cast<const uchar*>(msg.data().c_str()); 
                // QImage img = QImage(m_nVideoWidth, m_nVideoHeight, QImage::Format_RGB32);
                // uchar* pLine = img.scanLine(0); //获取图像数据指针基地址
                // memcpy(pLine, imgBuf, m_nVideoWidth * m_nVideoHeight);
                QImage img;
                img.loadFromData((uchar*)(msg.data().data()), len, "JPEG");
                QVideoFrame frame(img);
                if (m_call) {
                    m_call(frame);
                }
            } while (false);
        }
    } else {
        // 默认格式h264，解码h264
        ret = decodeH264(msg);
    }
    return ret;
}

int VideoDecoder::decodeH264(svbox::ImageFrame msg) {
    int ret = 0;
    uint64_t len = msg.data().size();
    av_new_packet(&m_Packet, len);
    m_Packet.stream_index = m_pCodecCtx->codec_type;
    memcpy(m_Packet.data, (uint8_t*)msg.data().data(), len);
    do {
        // 包发送到解码器
        ret = avcodec_send_packet(m_pCodecCtx, &m_Packet);
        if (ret < 0) {
            qDebug() <<  "Error while sending a packet to the decoder, ret = " << ret;
            //ret = -1;
            //break;
        }

        while (ret >= 0) {
            // 从解码器接收帧
            ret = avcodec_receive_frame(m_pCodecCtx, m_pFrame);
            if (ret == AVERROR(EAGAIN)) {
                ret = 0;
                break;
            }
            else if (ret == AVERROR_EOF) {
                ret = -1;
                break;
            }
            else if (ret < 0) {
                qDebug() << "Error while receiving a frame from the decoder";
                ret = -1;
                goto end;
            }
            qDebug() << "decode a frame to show, encode is h264....";
            sws_scale(m_pSwsContext, (const uint8_t* const*)m_pFrame->data, m_pFrame->linesize, 0, m_nVideoHeight, m_pconFrame->data, m_pconFrame->linesize);
            QImage img(m_pconFrame->data[0], m_nVideoWidth, m_nVideoHeight, QImage::Format_RGB32);
            QVideoFrame frame(img);
            if (m_call) {
                m_call(frame);
            }
        }
        av_packet_unref(&m_Packet);
    } while (false);
end:
    return 0;
}

int VideoDecoder::close()
{
    if (nullptr != m_pCodecCtx ) {
        avformat_close_input(&m_pFormatCtx);
        avformat_free_context(m_pFormatCtx);
        m_pCodecCtx = nullptr;
    }

    if (nullptr != m_pFrame) {
        av_frame_free(&m_pFrame);
    }

    if (nullptr != m_pconFrame ) {
        av_frame_free(&m_pconFrame);
    }

    if (nullptr != m_pSwsContext) {
        sws_freeContext(m_pSwsContext);
        m_pSwsContext = nullptr;
    }

    m_nVideoWidth = 0;
    m_nVideoHeight = 0;
    m_nVideoStreamIndex = -1;
    m_call = DecodeCall();
    return 0;

}

int VideoDecoder::width()
{
    return m_nVideoWidth;
}

int VideoDecoder::height()
{
    return m_nVideoHeight;
}

int VideoDecoder::lineSize()
{
    return width() * 4;
}

QVideoFrame::PixelFormat VideoDecoder::format()
{
    return QVideoFrame::Format_RGB32;
}

