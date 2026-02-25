#pragma once
#include<Bot/Meka.h>
#include<Pipeline/ConcurrentQueue.h>

void Meka::start(Strategy& strategy, CoinbaseAPI& api, AccountManager& account) {


    while (true) {
        if(!inTrade) {
            CandleData candle = candleData.popValue();
            Trade trade = strategy.next(candle);

            if(trade.tradeIntent != TradeIntent::NONE){
                account.placeTrade(api, trade);
            }    
        }
        else {
            
            // every 1 minute, we check the status of our trade
            std::this_thread::sleep_for(std::chrono::minutes(1));
        }
    }
}