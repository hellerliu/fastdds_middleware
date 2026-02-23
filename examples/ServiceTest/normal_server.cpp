#include "MyTestCallService.h"
#include "RpcCommu/NormalServer.h"


using namespace rpc;

int main()
{
    auto service = std::make_shared<mytest::MyTestCallService>();
    auto baseService = std::dynamic_pointer_cast<rpc::BaseService>(service);

    auto server = RpcCommu::NormalServer::create(baseService);

    while (true)
    {
        sleep(10);
    }
    return 0;
}
