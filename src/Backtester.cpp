#include <Backtester.h>
#include<thread>
#include<chrono>
#include<filesystem>
#include<format>


void Backtester::run(Strategy& strategy)
{
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("../../../data"))
    {
        if(dirEntry.path().string().substr(dirEntry.path().string().size() - 4) != ".csv")
            continue;

        std::this_thread::sleep_for(std::chrono::seconds(0));
        std::ifstream csv(dirEntry.path());

        if(!csv.is_open())
        {
            std::cout << "Could not open file csv" << std::endl;
            return;
        }
        //else {std::cout << "Opening file: " << dirEntry.path().string() << std::endl;}
        
        std::string row;

        //column headers
        std::getline(csv,row);

        while(std::getline(csv, row))
        {
            std::istringstream rowReader(row);
            CandleData candle;
            std::string field;


            // ------------- parse csv -> store as candle ----------------
            std::getline(rowReader, candle.timestamp, ','); //open timestamp

            std::getline(rowReader, field, ',');            //open price
            candle.open = std::stod(field);

            std::getline(rowReader, field, ',');            //high price
            candle.high = std::stod(field);

            std::getline(rowReader, field, ',');            //low price
            candle.low = std::stod(field);

            std::getline(rowReader, field, ',');            //close price
            candle.close = std::stod(field);

            std::getline(rowReader, field, ',');            //volume
            candle.volume = std::stod(field);
            // -----------------------------------------------------------

            //run candle through strategy and receive signal
            Trade trade = strategy.next(candle);

            //operate based off signal
            if(trade.tradeIntent != TradeIntent::NONE)
                paperAccount.enterPosition(trade);

            //check if candle triggers position closes
            paperAccount.checkOpenPositions(candle);
        }

        if(auto* supportresistance = dynamic_cast<SupportResistance*>(&strategy))
            supportresistance->clearWindow();
    }

    double wins = paperAccount.getWins();
    double losses = paperAccount.getLosses();
    double winrate = wins / (wins + losses) * 100;

    std::string finalBalStr = formatBalance(paperAccount.getBalance());
    std::string winrateStr = std::format("{:.2f}%", winrate);
    std::string winsStr = std::to_string(static_cast<int>(wins));
    std::string lossesStr = std::to_string(static_cast<int>(losses));

    //organize metrics into a table for output
    tabulate::Table metricsTable;
    metricsTable.add_row({"Final Balance", "Wins", "Losses", "Winrate"});
    metricsTable.add_row({finalBalStr, winsStr, lossesStr, winrateStr});
    metricsTable[1][0].format().font_color
        ((paperAccount.getBalance() >= 50000) 
            ? tabulate::Color::green 
            : tabulate::Color::red);

    std::cout << metricsTable << std::endl;
}