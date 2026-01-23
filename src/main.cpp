#include<iostream>
#include<DataPipeline.h>

typedef enum SelectedMode{NONE = 0, PIPELINE, BACKTESTER}SelectedMode;

int main() {

    std::cout << "Number of threads supported: " << std::thread::hardware_concurrency() << std::endl;

    int choice{0};
    while(choice != PIPELINE && choice != BACKTESTER)
    {
        std::cout <<"Select mode:\n"
                    "1 for pipeline\n"
                    "2 for backester\n";
        std::cin >> choice;
    }
    
    std::system("clear");

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
    }
}