#pragma once
#include <vector>
#include "Parser.h"
#include "Strategy.h"

class PaperAccount
{
public:
    PaperAccount(): balance_(50000), leverage_(10), makerFees_(0.02), takerFees_(0.05), inLong_(false), inShort_(false), currentRisk_(2.0)
    {riskLevels[2.0] = balance_; 
     riskLevels[1.0] = balance_;
     riskLevels[0.5] = balance_;}

    //setters
    //DONT use setBalance() to edit your balance mid engine run
    //PaperBank automatically manages risk, and using set balance
    //will interfere with the risk management. Only use to set initial bal
    void setBalance(double balance)     
    {balance_ = balance; 
     riskLevels[2.0] = balance; 
     riskLevels[1.0] = balance;
     riskLevels[0.5] = balance;}
    void setLeverage(int leverage)      { leverage_ = leverage; }
    void setMakerFees(double makerFees) { makerFees_ = makerFees; }
    void setTakerFees(double takerFees) { takerFees_ = takerFees; }

    //getters
    double getBalance() const           { return balance_; }
    int getLeverage() const             { return leverage_; }
    double getMakerFees() const         { return makerFees_; }
    double getTakerFees() const         { return takerFees_; }

    void enterPosition(Trade);
    void checkOpenPositions(CandleData);
private:
    struct Position
    {
        double entryPrice;
        double stopLossPrice;
        double targetProfitPrice;
        double stopLossPercent;
        double targetProfitPercent;
        double positionSize;
        bool active = false;
        TradeIntent tradeType = TradeIntent::NONE;
    };

    void adjustRisk();

    std::unordered_map<double, double> riskLevels;
    Position position;
    double currentRisk_;
    double balance_;
    double makerFees_; 
    double takerFees_; 
    int leverage_;
    bool inLong_;
    bool inShort_;
    
};