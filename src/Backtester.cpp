#include <Backtester.h>

void Backtester::run(Strategy& strategy)
{

    while(true)
    {
        //parse csv
        
        //run candle through strategy and receive signal
        Trade signal = strategy.next(CandleData());

        //operate based off signal
        if(signal.tradeIntent == TradeIntent::ENTER)
        {
            
        }
    }
}