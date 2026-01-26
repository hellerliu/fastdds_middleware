#pragma once

#include "IFiberCall.h"
#include "IMyTestCall.h"
#include "marl/event.h"
#include "RpcCore/FiberThread.h"

int funcCall1(int index, const std::string &message, std::string &respMSg)
{
    sleep(2);
    respMSg = message + " world";
    return index + 1;
}

int funcCall2(int index, const std::string &message, std::string &respMSg)
{
    marl::Event sleep{marl::Event::Mode::Auto};
    sleep.wait_for(std::chrono::seconds{2});

    respMSg = message + " world";
    return index + 1;
}

class FiberCallService : public IFiberCall
{
public:
    FiberCallService() : IFiberCall(false)
    {
        other_thread_ = rpc::FiberThread::create();
    }

    ~FiberCallService()
    {
        other_thread_->stopThread();
    }

    int fiberTest(const EchoMessage &req, proto::EchoMessage &resp) override
    {
        if (req.index == 1)
        {
            // marl 切换协程
            printf("sleep enter: %d %s\n", req.index, req.message.c_str());

            marl::Event sleep{marl::Event::Mode::Auto};
            sleep.wait_for(std::chrono::seconds{2});

            resp.set_index(req.index + 1);
            std::string message = req.message + " world";
            resp.set_message(message);
            printf("sleep exit: %d %s\n", req.index, req.message.c_str());
        }
        else if (req.index == 2)
        {
            // 新的线程 切换协程
            printf("async_thread enter: %d %s\n", req.index, req.message.c_str());

            std::string message;
            int res = rpc::fiber_async(funcCall1, req.index, req.message, message);
            resp.set_index(res);
            resp.set_message(message);
            printf("async_thread exit: %d %s\n", req.index, req.message.c_str());
        }
        else if (req.index == 3)
        {
            // 一个线程队列 切换协程
            printf("FiberThread enter: %d %s\n", req.index, req.message.c_str());

            std::string message;
            int res = other_thread_->sendCall(true, funcCall2, req.index, req.message, message);
            resp.set_index(res);
            resp.set_message(message);
            printf("FiberThread exit: %d %s\n", req.index, req.message.c_str());
        }
        else if (req.index == 4)
        {
            // 另一个rpc同步请求 切换协程
            printf("rpc_call enter: %d %s\n", req.index, req.message.c_str());

            std::string message;
            int res = test_call_.fiberTest(req.message, message);
            resp.set_index(req.index + 1);
            resp.set_message(message);

            printf("rpc_call exit: %d %s\n", req.index, req.message.c_str());
        }
        return 0;
    }

private:
    //
    std::shared_ptr<rpc::FiberThread> other_thread_;
    mytest::IMyTestCall test_call_;
};
