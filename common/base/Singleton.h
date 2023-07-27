#ifndef SINGLETON_H
#define SINGLETON_H

#include <mutex>

//单例模板类
template <class T>
class Singleton
{
public:
    static T* getInstance()
    {
        if (m_pInstance == nullptr)  //判断是否第一次调用
        {
            m_locker.lock();
            if (m_pInstance == nullptr)
            {
                m_pInstance = new T();
            }
            m_locker.unlock();
        }
        return m_pInstance;
    }

protected:
    //使继承者无法public构造函数和析构函数
    Singleton() {}
    ~Singleton() {}

private:
    //禁止拷贝构造和赋值运算符. The only way is getInstance()
    Singleton(const Singleton& src) = delete;
    Singleton &operator=(const Singleton& src) = delete;

    class Garbo   //它的唯一工作就是在析构函数中析构Singleton的实例，所以private
    {
    public:
        ~Garbo()
        {
            if (Singleton::m_pInstance)
            {
                delete Singleton::m_pInstance;
                Singleton::m_pInstance = nullptr;
            }
        }
    };

private:
    static std::mutex   m_locker;
    static T*           m_pInstance;
    static Garbo        m_garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数，
                                  //我们不需要访问这个变量，所以不需要初始化
};

template <typename T>
std::mutex Singleton<T>::m_locker;

template <class T>
T* Singleton<T>::m_pInstance = nullptr; //必须初始化这个静态成员，初始化的过程中会分配内存，否则无法访问


#endif // SINGLETON_H
