#pragma once

#include"Pipeline/ConcurrentQueue.h"
#include<chrono>

// async logger
inline void logger() {
    while (true) {
        const auto& msg = logs.popValue();

        auto latency = std::chrono::duration_cast<std::chrono::microseconds>(msg.latencyTimestamp - msg.candle.latencyTimestamp).count();
        std::cout << "Socket -> DBwrite Latency: " << latency << " microseconds\n";
    }
}