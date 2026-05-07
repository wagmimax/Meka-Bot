#pragma once
#include<Bot/Meka.h>
#include<Pipeline/ConcurrentQueue.h>

void Meka::start(Strategy& strategy, AccountManager& account) {

    std::string order_id;
    
    // This loop is messy. will probably change internals later to make it more clean
    while (true) {
        if(!inTrade) {
            CandleData candle = candleData.popValue();
            Trade trade = strategy.next(candle);

            if(trade.tradeIntent != TradeIntent::NONE){
                std::cout << "TRADE SIGNAL DETECTED\n";
                order_id = account.placeTrade(trade);
                inTrade = (order_id != "") ? true : false; 
            }    
        }
        else {

            std::cout << "MONITORING OPEN TRADE...\n"; 
            account.monitorTrade(order_id);
            std::cout << "TRADE EXIT FILLED\n";
            inTrade = false; 
            strategy.reset();
            candleData.clearData();
            std::cout << "NO LONGER IN TRADE, STRATEGY RESET, QUEUE CLEARED\n";
        }
    }
}
