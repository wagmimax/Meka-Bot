A dev's tool for working with crypto data

My program has two parts:  
-Live crypto data pipeline  
-Strategy backtester  

I eventually hope to connect the two for backtesting on live data, and am actively working on this project.

If you want to add your own strategies for testing, you mainly need to edit Strategy.h and Strategy.cpp.
Each strategy must return an entry price, stoploss, and a TradeIntent to signal long or short. 
I built the backtester to automatically manage bankroll.

Eventually, I hope to add a live trading bot. But is it even possible to create a profitable live trading bot?