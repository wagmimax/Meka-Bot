#include<ConcurrentQueue.h>
#include<Parser.h>

void parseData()
{
    std::cout << "Begin parsing" << std::endl;
    nlohmann::json json;
    using namespace std;

    while(true)
    {
        TimestampedMessage rawJSON = rawData.popValue();
        // auto start = std::chrono::high_resolution_clock::now();
        try
        {
            json = nlohmann::json::parse(rawJSON.json);

            const auto& trades = json["events"][0]["trades"];

            //coinbase sends batch trades in an array when they happen in the same microsecond
            for(const auto& trade : trades)
            {
                tradeData.push(TradeData{
                    trade["product_id"].get<std::string>(), 
                    trade["time"].get<std::string>(), 
                    std::stod(trade["price"].get<std::string>()), 
                    std::stod(trade["size"].get<std::string>()),
                    rawJSON.latencyTimestamp
                });
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error processing trade: " << e.what() << std::endl;
        }
        // auto end = std::chrono::high_resolution_clock::now();
        // std::cout << "Parser latency: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";
    }
}