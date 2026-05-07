#ifndef BOT_MEKA_H
#define BOT_MEKA_H

#include"CoinbaseAPI.h"
#include"Backtester/Strategy.h"
#include"Bot/AccountManager.h"  // this can cause circular include 

// Crypto Trading Bot
class Meka {
public:
    void start(Strategy&, AccountManager&);
    
private:
    bool inTrade = false;
};

#endif // BOT_MEKA_H
