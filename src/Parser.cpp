#include<ConcurrentQueue.h>
#include<Parser.h>

void parseData()
{
    std::cout << "Begin parsing" << std::endl;
    std::string stringJSON;
    nlohmann::json json;

    while(true)
    {
        stringJSON = rawData.pop();
        json = nlohmann::json::parse(stringJSON);

        std::cout << json["s"];
    }

}