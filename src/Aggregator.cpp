#include<Aggregator.h>

void Aggregate()
{
    std::unordered_map<std::string, CandleData> candles;

    candles.emplace("BTC", CandleData("BTC", -1, -1, -1, -1, -1, "temp"));
    candles.emplace("ETH", CandleData("ETH", -1, -1, -1, -1, -1, "temp"));
    candles.emplace("SOL", CandleData("SOL", -1, -1, -1, -1, -1, "temp"));

    while(true)
    {
        TradeData currentTrade = tradeData.popValue();

        std::string ticker = currentTrade.ticker.substr(0, 3);
        std::string currentMinute = currentTrade.time.substr(14, 2);

        //coinbase tends to send trades that happened a minute ago. ignore them
        if (candles.at(ticker).startTime != "temp" && currentMinute < candles.at(ticker).startTime)
            if(!(candles.at(ticker).startTime == "59" && currentMinute == "00")) //cover edge case: MM wraps to 00 after hitting the hour mark
                continue;

        //initialize new candle when minute changes
        if(candles.at(ticker).startTime != currentMinute)
        {
            if(candles.at(ticker).startTime != "temp")
            {
                std::cout << candles.at(ticker).startTime << " Candle Closed. OHLC: " << candles.at(ticker).open 
                    << " High: " << candles.at(ticker).high << " Low: " << candles.at(ticker).low 
                    << " Close: " << candles.at(ticker).close << std::endl;
            }
            
            candles[ticker].open = currentTrade.price;
            candles[ticker].high = currentTrade.price;
            candles[ticker].low = currentTrade.price;
            candles[ticker].close = currentTrade.price;
            candles[ticker].volume = 0;
            candles[ticker].startTime = currentMinute;
        }

        //update current candle
        candles[ticker].close = currentTrade.price;
        candles[ticker].volume += currentTrade.volume;

        if(candles.at(ticker).high < currentTrade.price)
            candles[ticker].high = currentTrade.price;
        else if(candles.at(ticker).low > currentTrade.price)
            candles[ticker].low = currentTrade.price; 
    }
}