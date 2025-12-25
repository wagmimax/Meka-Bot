#pragma once
#include <vector>
#include "Parser.h"
#include "Strategy.h"

class PaperAccount
{
public:
    //maker and taker fees defaulted to coinbase spot trading
    PaperAccount(): balance_(50000), leverage_(1), makerFees_(0.4), takerFees_(0.6), inLong_(false), inShort_(false)
    {}

    //setters
    void setBalance(double balance)     { balance_ = balance; }
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
        double entry;
        double stopLoss;
        double targetProfit;
    };

    double calculatePosition(const double& stopLoss);

    std::vector<Position> positions;
    double balance_;
    double makerFees_; 
    double takerFees_; 
    int leverage_;
    bool inLong_;
    bool inShort_;
    
};