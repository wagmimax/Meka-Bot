#pragma once
#include "Parser.h"
#include<deque>

enum struct TradeIntent
{
    NONE,
    LONG,
    SHORT
};

//Every strategy must return whether it wants to enter a trade or not,
//passing along an entry price level and stoploss percent. PaperBank 
//will handle all calculations based off the entry and stoploss percent
struct Trade
{   
    TradeIntent tradeIntent;
    double entryLevel;
    double stopLossPercent;
};

class Strategy
{
public:
    virtual Trade next(CandleData) {std::cout << "Entity" << std::endl; return Trade{};};

private:
    
};

class SupportResistance : public Strategy
{
public:
    SupportResistance():
    resistance({0,0,0,false}), 
    support({std::numeric_limits<double>::max(),0,0,false}), 
    tolerance(0.0005) 
    {}

    Trade next(CandleData) override;
private:
    struct Level
    {
        double price;
        int touches;
        int age;
        bool active;
    };

    Level resistance;
    Level support;
    std::deque<CandleData> rollingWindow;
    double tolerance;
};