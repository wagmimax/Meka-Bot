#include<iostream>
#include<WebSocketClient.h>
#include<ConcurrentQueue.h>
#include<thread>
#include<Database.h>

int main() {
    WebSocketClient binanceStream("stream.binance.us", "9443", "/ws"
        "/btcusdt@kline_1m/btcusdt@kline_5m/btcusdt@kline_15m"
        "/solusdt@kline_1m/solusdt@kline_5m/solusdt@kline_15m"
        "/ethusdt@kline_1m/ethusdt@kline_5m/ethusdt@kline_15m");

    std::vector<std::string> pairs = {"BTCUSDT", "SOLUSDT", "ETHUSDT"};
    initTables(pairs);

    std::thread socketWorker(&WebSocketClient::run, &binanceStream);
    std::thread parseWorker(parseData);

    socketWorker.join();
    parseWorker.join();
}