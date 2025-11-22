#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<nlohmann/json.hpp>

struct CandleData
{
    CandleData(const std::string& ticker,const int& openTime,const int& closeTime, const int& openPrice, const int& closePrice,
        const int& high, const int& low, const bool& closed);

    std::string ticker;
    int openTime;
    int closeTime;
    int openPrice;
    int closePrice; //keeps changing until the candle closes
    int high;
    int low;
    bool closed;
};

void parseData();