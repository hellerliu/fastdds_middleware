#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>

#include "IMyTestCall.h"
#include "marl/event.h"
#include "marl/blockingcall.h"

namespace mytest
{
    class MyTestCallService : public IMyTestCall
    {
    public:
        unsigned int num_ = 0;
        unsigned long time_now_ = 0;
        unsigned int num_tmp_ = 0;

        MyTestCallService() : IMyTestCall(false)
        {
        }

        int addOne(const int &req, int &resp) override
        {
            printf("addOne req = %d\n", req);
            resp = req + 1;
            return 0;
        }

        int fiber_test(const std::string &req, echoResp &resp) override
        {
            marl::blocking_call([req]
                                {
                pid_t tid = gettid();
                printf("fiber_thread new thread run:%d %s\n",tid, req.c_str());
                sleep(1); });

            resp.data = 6;
            printf("fiber_thread exit\n");
            return 0;
        }

        int returnError(const rpc::VoidParam &req, rpc::VoidParam &resp) override
        {
            return ReturnTestError;
        }

        int array_test(const int (&req)[2], int (&resp)[2]) override
        {
            resp[0] = req[1];
            resp[1] = req[0];
            printf("array_test: %d %d\n", resp[0], resp[1]);
            return 0;
        }

        int fiberTest(const std::string &req, std::string &resp) override
        {
            printf("MyTestCallService fiberTest enter\n");
            marl::Event sleep{marl::Event::Mode::Auto};
            sleep.wait_for(std::chrono::seconds{2});
            resp = req + " world";
            return 0;
        }
    };

}
