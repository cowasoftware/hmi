#pragma once

#include <functional>
#include <QObject>
#include <QThread>

class Task : public QObject
{
    Q_OBJECT

Q_SIGNALS:

    void finished(void *data);

public:
    Task(std::function<void *(void *)> func) : _func(std::move(func)) {}

public:
    void start() { metaObject()->invokeMethod(this, "run"); }

private Q_SLOTS:
    void run()
    {
        void *data = _func(nullptr);
        Q_EMIT finished(data);
    }

private:
    std::function<void *(void *)> _func;
};

class AsyncInvoker : public QObject
{
    Q_OBJECT
public:
    AsyncInvoker(QObject *parent = nullptr) : QObject(parent)
    {
        _thread.start();
    }

    ~AsyncInvoker()
    {
        _thread.exit();
        _thread.wait();
    }

    template <typename T>
    void invoke(std::function<T(void)> task, std::function<void(T &&)> callback = std::function<void(T &&)>(), QObject *target = nullptr)
    {
        if (target == nullptr)
        {
            target = this;
        }
        auto task_wrapper = [task](void *) -> void *
        {
            return static_cast<void *>(new T(std::move(task())));
        };

        auto task_obj = new Task(task_wrapper);

        auto callbacak_wrapper = [callback, task_obj](void *data)
        {
            if(callback)
            {
                callback(std::forward<T>(*static_cast<T *>(data)));
            }
            delete static_cast<T *>(data);
            task_obj->deleteLater();
        };

        connect(task_obj, &Task::finished, target, callbacak_wrapper);
        task_obj->moveToThread(&_thread);
        task_obj->start();
    }

private:
    QThread _thread;
};