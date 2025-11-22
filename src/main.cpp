#include<iostream>
#include<WebSocketClient.h>
#include<ConcurrentQueue.h>
#include<thread>

int main() {
    WebSocketClient binanceStream("stream.binance.us", "9443", "/ws/btcusdt@kline_1m");

    std::thread socketWorker(&WebSocketClient::run, &binanceStream);
    std::thread parseWorker(parseData);

    socketWorker.join();
    parseWorker.join();
}