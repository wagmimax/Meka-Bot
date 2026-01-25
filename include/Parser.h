#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<chrono>

struct CandleData
{
    
    
    double close;
    double high;
    double low;
    double volume;
    double open;

    std::string ticker;
    std::string timestamp;
    std::string minute;
    std::chrono::time_point<std::chrono::high_resolution_clock> latencyTimestamp;

    CandleData() 
        : close(-1), high(-1), low(-1), volume(-1), open(-1), ticker(""), timestamp(""), minute(""), latencyTimestamp(std::chrono::high_resolution_clock::now()) {}

    CandleData(const std::string& ticker, double open, double close,
        double high, double low, double volume, const std::string& timestamp, 
        const std::string& minute, std::chrono::time_point<std::chrono::high_resolution_clock> latencyTimestamp):
        ticker(ticker), open(open), close(close), high(high), low(low), volume(volume), timestamp(timestamp), minute(minute), 
        latencyTimestamp(latencyTimestamp) {}
};

struct TradeData
{
    std::string ticker;
    std::string time;
    double price;
    double volume;
    std::chrono::time_point<std::chrono::high_resolution_clock> latencyTimestamp;

    TradeData() = default;

    TradeData(const std::string& ticker, const std::string& time, double price, double volume, 
        std::chrono::time_point<std::chrono::high_resolution_clock> latencyTimestamp):
        ticker(ticker), time(time), price(price), volume(volume), latencyTimestamp(latencyTimestamp) {}
};

struct TimestampedMessage
{
    std::string json;
    std::chrono::time_point<std::chrono::high_resolution_clock> latencyTimestamp;

    TimestampedMessage() = default;

    TimestampedMessage(const std::string& json, std::chrono::time_point<std::chrono::high_resolution_clock> latencyTimestamp):
    json(json), latencyTimestamp(latencyTimestamp) {};
};

struct LoggerFormat {
    CandleData candle;
    std::chrono::time_point<std::chrono::high_resolution_clock> latencyTimestamp;

    LoggerFormat() = default;

    LoggerFormat(CandleData candle, std::chrono::time_point<std::chrono::high_resolution_clock> latencyTimestamp): candle(candle), latencyTimestamp(latencyTimestamp) {};
};

void parseData();