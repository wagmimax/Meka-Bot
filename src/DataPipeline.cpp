#include<DataPipeline.h>

void Pipeline::start() {

    std::thread socketWorker(&WebSocketClient::run, &coinbaseStream_);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    //flush any bad data in the beginning 
    rawData.clearData();
    tradeData.clearData();

    std::thread parseWorker(parseData);
    std::thread aggregateWorker(Aggregate, std::ref(database_));
    std::thread pipeWorker(&NamedPipe::sendData, &server_);

    socketWorker.join();
    parseWorker.join();
    aggregateWorker.join();
    pipeWorker.join();
}