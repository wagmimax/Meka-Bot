#include<Aggregator.h>
#include<unordered_map>

void Aggregate(Database& sqliteDB, const std::vector<std::string> pairs)
{
    std::unordered_map<std::string_view, CandleData> currentCandles;

    
        currentCandles.emplace("BTC", CandleData("BTC", -1, -1, -1, -1, -1, "temp", "temp", std::chrono::high_resolution_clock::now()));
            currentCandles.emplace("ETH", CandleData("ETH", -1, -1, -1, -1, -1, "temp", "temp", std::chrono::high_resolution_clock::now()));
        currentCandles.emplace("SOL", CandleData("SOL", -1, -1, -1, -1, -1, "temp", "temp", std::chrono::high_resolution_clock::now()));



    std::unordered_map<std::string_view, std::string> lastTimestamp;

    lastTimestamp["BTC"] = "";
    lastTimestamp["ETH"] = "";
    lastTimestamp["SOL"] = "";

    while(true)
    {
        TradeData currentTrade = tradeData.popValue();

        // auto start = std::chrono::high_resolution_clock::now();
        
        std::string_view ticker(currentTrade.ticker.c_str(), 3);
        std::string_view currentMinute(currentTrade.time.c_str() + 14, 2);

        //coinbase sends old trade data sometimes. needs to be ignored
        if (!lastTimestamp[ticker].empty() && currentTrade.time < lastTimestamp[ticker])
            continue;
        lastTimestamp[ticker] = currentTrade.time;

        auto& candle = currentCandles[ticker];

        //initialize new candle when minute changes
        if(candle.minute != currentMinute)
        {
            if(candle.minute != "temp")
            {
                candle.latencyTimestamp = currentTrade.latencyTimestamp;
                sqliteDB.writeData(candle);
                // std::cout << candle.minute << " Candle Closed. OHLC: " << candle.open 
                //     << " High: " << candle.high << " Low: " << candle.low 
                //     << " Close: " << candle.close << " Timestamp: " << candle.timestamp << std::endl;
            }
            
            candle.open = currentTrade.price;
            candle.high = currentTrade.price;
            candle.low = currentTrade.price;
            candle.close = currentTrade.price;
            candle.volume = 0;
            candle.minute = currentMinute;
            candle.timestamp = currentTrade.time;
        }

        //update current candle
        candle.close = currentTrade.price;
        candle.volume += currentTrade.volume;
        if(candle.high < currentTrade.price) candle.high = currentTrade.price;
        if(candle.low > currentTrade.price) candle.low = currentTrade.price; 

        candleData.push(candle);

        // auto end = std::chrono::high_resolution_clock::now();
        // std::cout << "Aggregator latency: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "\n";
    }
}