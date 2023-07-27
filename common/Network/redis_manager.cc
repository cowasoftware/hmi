#include "redis_manager.h"
#include <QDebug>
#include <functional>
#include <thread>
#include <iostream>


RedisManager::RedisManager(QObject *parent) {
}

RedisManager::RedisManager(std::string ip, int port)
{
    std::cout << "Redis client is created, redis server running on ip[" << ip << "], port[" << port << "]" << std::endl;
    m_ip = ip;
    m_port = port;
    m_context = nullptr;
    m_asyncContext = nullptr;
    m_reply = nullptr;
}

void RedisManager::handleRedisReply(redisReply* _redisReply) {
    if(_redisReply == NULL) {
        return;
    }
    std::cout << "handleRedisReply, reply type is: " << _redisReply->type << std::endl;
    switch(_redisReply->type) {
        case REDIS_REPLY_STRING:
            // 返回字符串
            Q_EMIT notifyRedisResult(_redisReply->str);
            break;
        case REDIS_REPLY_ARRAY:
            // TODO used for future
            break;
        case REDIS_REPLY_INTEGER:
            // TODO used for future
            break;
        case REDIS_REPLY_NIL:
            // TODO used for future
            std::cout << "handleRedisReply:: key is not exist!!!" << std::endl;
            break;
        case REDIS_REPLY_STATUS:
            // set successful, return ok
            std::cout << "handleRedisReply:: execute command success" << std::endl;
            break;
        case REDIS_REPLY_ERROR:
            break;
        default:
            std::cout << "handleRedisReply:: Redis server has no response!!!" << std::endl;
            break;
    }
    // 处理完后释放
    freeRedis();

}

void RedisManager::comandCallback(redisAsyncContext *ctx, void *r, void *privdata) {
    redisReply* reply = static_cast<redisReply *>(r);
    std::cout << "reply type: " << reply->type << std::endl;
    RedisManager* manager = static_cast<RedisManager *>(privdata);
    if(reply == nullptr || manager == nullptr) {
        return;
    }
    manager->handleRedisReply(reply);
}


bool RedisManager::connectRedis() {
    if(m_context == NULL) {
        struct timeval t;
        t.tv_sec = 3;
        t.tv_usec = 0;
        m_context = redisConnectWithTimeout(m_ip.c_str(), m_port, t);
    }
    std::cout << "m_context = " << m_context << std::endl;
    if(m_context == NULL) {
        std::cout << "Failed to connect redis, redisContext is empty!!!" << std::endl;
        return false;
    }
    if(m_context->err != 0) {
        std::cout << "Failed to connect redis, error message is "<< m_context->errstr << std::endl;
        redisFree(m_context);
        return false;
    }
    std::cout << "Successed to connect redis server." << std::endl;
    return true;
}

bool RedisManager::connectRedisAsync() {
    if(m_asyncContext == NULL) {
        m_asyncContext = redisAsyncConnect(m_ip.c_str(), m_port);
    }
    if(m_asyncContext == NULL) {
        std::cout << "Failed to asyncConnect redis, redisAsyncContext is null!!!" << std::endl;
        return false;
    }
    if(m_asyncContext->err) {
        std::cout << "Failed to asyncConnect redis, error message is: , "<<m_asyncContext->errstr << std::endl;
        redisAsyncFree(m_asyncContext);
        return false;
    }
    std::cout << "Successed to asyncConnect redis server." << std::endl;
    return true;
}

void RedisManager::execRedis(const std::string cmd) {
    // 开启子线程
    std::thread _thread([&, cmd](){
        // 1、连接
        bool connected = connectRedis();
        std::cout << "connected status: " << connected << std::endl;
        if(connected) {
            // 2、执行
            m_reply = (redisReply*)redisCommand(m_context, cmd.c_str());
            std::cout << "Succeed to execute command[" << cmd << "], result is [" << m_reply->str << "]" << std::endl;
            handleRedisReply(m_reply);
        }
    });
    _thread.detach();
}

void RedisManager::execRedisAsync(const std::string cmd) {
    bool connected = connectRedisAsync();
    if(connected) {
        std::cout << "execRedisAsync::cmd: " << cmd << std::endl;
        // std::function<void*(redisAsyncContext *, void *, void *)> call = std::bind(&RedisManager::setCallback,this,std::placeholders::_1,
        // std::placeholders::_2, std::placeholders::_3);
        int result = redisAsyncCommand(m_asyncContext, comandCallback, this, cmd.c_str());
        if(result == REDIS_ERR) {
            std::cout << "execute commond failed: " << result << std::endl;
        }
    }
}

void RedisManager::freeRedis() {
    if(m_context) {
        redisFree(m_context);
    }
    if(m_asyncContext) {
        redisAsyncFree(m_asyncContext);
    }
    freeReply();
    destroyRedis();
}

void RedisManager::freeReply() {
    if(m_reply != NULL) {
        freeReplyObject(m_reply);   
    }
}

void RedisManager::destroyRedis() {
    std::cout << __FUNCTION__ << " is called." << std::endl;
    m_context = nullptr;
    m_asyncContext = nullptr;
    m_reply = nullptr;
}

RedisManager::~RedisManager()
{
}