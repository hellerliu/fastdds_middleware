#include "RpcCommu/ChannelFactory.h"
#include "RpcCommu/ChannelSubscriber.h"
#include "RpcCommu/ChannelPublisher.h"
#include "helloworld_zc/msg/HelloWorldPubSubTypes.hpp"
#include <functional>
#include <unistd.h>

#include <fastdds/dds/log/Log.hpp>
#include <sys/types.h>

using namespace RpcCommu;
using namespace helloworld_zc::msg;

int main()
{
    eprosima::fastdds::dds::Log::SetVerbosity(eprosima::fastdds::dds::Log::Info);
    auto publisher = ChannelPublisher<HelloWorldPubSubType, true>::create("hello_world");

    int index = 0;  
    while (true)
    {
        HelloWorld* msg = publisher->loanMessage();
        
        msg->index(index);
        index++;
        msg->data()[0] = 1;
        msg->data()[1] = 2;

        int res = publisher->publish(*msg);
        printf("pub:%d %d\n", msg->index(), res);

        sleep(1);
    }

    return 0;
}