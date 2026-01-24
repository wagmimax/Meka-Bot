#include<DataPipeline.h>

void Pipeline::start() {

    threads_.emplace_back(&WebSocketClient::run, &coinbaseStream_);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    //flush any bad data in the beginning 
    rawData.clearData();
    tradeData.clearData();

    threads_.emplace_back(parseData);
    threads_.emplace_back(Aggregate, std::ref(database_), std::ref(pairs_));
    threads_.emplace_back(&NamedPipe::sendData, &server_);

    for(auto& thread : threads_) {
        if(thread.joinable()) {
            thread.join();
        }
    }
}