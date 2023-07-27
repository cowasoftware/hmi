#pragma once

#ifndef REDISMANAGER_H
#define REDISMANAGER_H
#include <QObject>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

class RedisManager : public QObject
{
    Q_OBJECT
public:
    RedisManager(QObject *parent = nullptr);
    RedisManager(std::string ip, int port);
    bool getConnect();
    // 同步方法
    void execRedis(const std::string cmd);
    // 异步执行
    void execRedisAsync(const std::string cmd);
    // 释放
    void freeRedis();
    void freeReply();

    ~RedisManager();

private:
    bool connectRedis();
    // 异步连接
    bool connectRedisAsync();
    // 异步回调
    static void comandCallback(redisAsyncContext *, void *, void *);
    void handleRedisReply(redisReply* _redisReply);
    void destroyRedis();

friend
    // 异步回调
    void getCallback(redisAsyncContext *, void *, void *);

Q_SIGNALS:
    void notifyRedisResult(QString result);

private:
    std::string m_ip;
    int m_port;
    redisContext* m_context;
    redisAsyncContext* m_asyncContext;
    redisReply* m_reply;
};

#endif

