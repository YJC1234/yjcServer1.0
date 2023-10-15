#include <logConfig/yjcServer.h>
#include <iostream>
#include <vector>

long long  count = 0;
std::mutex mutex;

void fun1() {
    spdlog::info("name:{},this.name{}; id:{};",
                 yjcServer::Thread::GetName(),
                 yjcServer::Thread::GetThis()->getName(),
                 yjcServer::Thread::GetThis()->getId());
    for (int i = 0; i < 1000000; i++) {
        count = count + 1;
    }
}

void fun2() {}

int main() {
    std::vector<yjcServer::Thread::ptr> thrs;
    for (int i = 0; i < 5; i++) {
        yjcServer::Thread::ptr thr(
            new yjcServer::Thread(fun1, "fun" + std::to_string(i)));
        thrs.push_back(std::move(thr));
    }
    for (int i = 0; i < 5; i++) {
        thrs[i]->join();
    }
    spdlog::info("count = {}", count);
}