#include<iostream>
#include<Pipeline/DataPipeline.h>
#include<Backtester/Backtester.h>
#include<Bot/Meka.h>

typedef enum SelectedMode{PIPELINE = 1, BACKTESTER, BOT}SelectedMode;

int main() {

    std::cout << "Number of threads supported: " << std::thread::hardware_concurrency() << std::endl;

    int choice {};
    while(choice != PIPELINE && choice != BACKTESTER && choice != BOT)
    {
        std::cout <<"Select mode:\n"
                    "[1] Pipeline\n"
                    "[2] Backester\n"
                    "[3] Meka\n";
        std::cin >> choice;
    }


    const SelectedMode selectedMode = static_cast<SelectedMode>(choice);
 
    switch (selectedMode)
    {
        case PIPELINE:
        {
            Pipeline pipeline;
            pipeline.start();

        }break;
        case BACKTESTER:
        {
            Backtester backtester;
            SupportResistance supportResistance;
            backtester.run(supportResistance);
        }break;
        case BOT:
        {
            std::cout << "1";
            std::ifstream inFile("../../secret.pem");
            std::stringstream keystream;
            keystream << inFile.rdbuf();
            std::cout << "2";
            std::string key_name = std::getenv("COINBASE_KEY");
            std::cout << "3";
            std::string key_secret = keystream.str();
            std::cout << "4";
            
            CoinbaseAPI api(key_name, key_secret);
            AccountManager man(api); 
            CoinFlip coinFlip;
            Meka meka;
            
            Pipeline pipeline;
            pipeline.start(std::thread(&Meka::start, &meka, std::ref(coinFlip), std::ref(man)));
        }break;
    }
}
