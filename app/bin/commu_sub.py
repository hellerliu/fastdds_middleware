#!/usr/bin/python3

import sys
sys.path.append("../lib")

import time
import RpcCommu
import HelloWorld
import asyncio

# async or not
def handleHelloWorld(msg : HelloWorld.HelloWorld):
    print("py sub:{} {}".format(msg.index(), RpcCommu.get_thread_tid()))

async def handleHelloWorld_async(msg : HelloWorld.HelloWorld):
    print("py sub async:{} {}".format(msg.index(), RpcCommu.get_thread_tid()))
    await asyncio.sleep(5)
    print("py sub async end:{}".format(msg.index()))


timeID1 = 0
def timeCallBack(count):
    print(f"time callback {count["value"]}")
    if(count["value"] == 6):
        RpcCommu.get_handle_thread().remove_timer(timeID)
 

if __name__ == "__main__":
    subscriber = RpcCommu.ChannelSubscriber(HelloWorld.HelloWorldPubSubType, "hello_world", handleHelloWorld)
    subscriber1 = RpcCommu.ChannelSubscriber(HelloWorld.HelloWorldPubSubType, "hello_world", handleHelloWorld_async)

    count = {"value" : 0}
    timeID = RpcCommu.get_handle_thread().add_timer(1.0, True, timeCallBack, count)
 
    timeID1 = RpcCommu.get_handle_thread().add_timer(1.0, False, timeCallBack, count)    
    
    while True:
        time.sleep(1) 
        count["value"] += 1
        '''
        if(count["value"] == 5):
            RpcCommu.get_handle_thread().remove_timer(timeID)
        '''

    exit()



