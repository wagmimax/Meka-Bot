#include<iostream>
#include<WebSocketClient.h>

int main() {
    std::cout << "Test";

    WebSocketClient BTC("stream.binance.com", "9443", "/ws/btcusdt@trade");
}