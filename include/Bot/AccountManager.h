#ifndef BOT_ACCOUNT_MANAGER_H
#define BOT_ACCOUNT_MANAGER_H

#include"Backtester/Strategy.h"
#include"Bot/CoinbaseAPI.h"
#include<unordered_map>

class AccountManager {
public:
    AccountManager(CoinbaseAPI& api);

    std::string placeTrade(Trade&);
   
    // This method blocks until an exit order is filled
    void monitorTrade(std::string_view order_id);
private:
    void adjustRisk();

    std::unordered_map<double, double> riskLevels;
    CoinbaseAPI api_;
    double currentRisk_;
    double balance_;
    double excessBal_;
    double makerFees_; 
    double takerFees_; 
    int RR_;
    int wins;
    int losses;
    bool DEBUGGING_ON;
};

#endif // BOT_ACCOUNT_MANAGER_H
