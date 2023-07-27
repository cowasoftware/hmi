#pragma once

/**
 * ��Դ������
*/
class Manager
{
private:
    Manager(/* args */);
    ~Manager();
public:
    static Manager& getInstance();

    /**
     * ��ʼ����Դ
    */
     void init();

    // 车辆异常处理
    void handleExceptionOp();

    /***
     * �ͷ���Դ
    */
     void destroy();
    
private:
     void initService();

     void initQmlRegister();

     void initConfigInfo();
    
};
