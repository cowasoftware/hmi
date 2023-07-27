#include "helper.h"


void set_thread_name(const std::string& thread_name)
{
    if(ERANGE == pthread_setname_np(pthread_self(), thread_name.c_str()))
    {
        std::cout << "set_thread_name:" << thread_name << " is error" << std::endl;
    }
    std::cout << thread_name << " start id:" << std::this_thread::get_id() << std::endl;
}

void uint32_to_request_status_enum(uint32_t status)
{
    switch (status)
    {
        case request_response::ResponseStatusType_RequestStatusEnum_NO_REQUEST:
            std::cout << "NO_REQUEST" << std::endl;
            break;
        case request_response::ResponseStatusType_RequestStatusEnum_REQUEST_SUCC:
            std::cout << "REQUEST_SUCC" << std::endl;
            break;
        case request_response::ResponseStatusType_RequestStatusEnum_REQUEST_FAIL:
            std::cout << "REQUEST_FAIL" << std::endl;
            break;
        case request_response::ResponseStatusType_RequestStatusEnum_REQUEST_WAIT:
            std::cout << "REQUEST_WAIT" << std::endl;
            break;
        default:
            std::cout << "REQUEST_ERROR" << std::endl;
            break;
    }
}