WIP - This software is my take on creating an algorithmic trading system.  
  
As of now, I built it for myself and I have much more work to do. Therefore, I will hold off on documentation until I believe my software is stable enough.  


# Meka-Bot  
Meka-Bot is a bot that programmatically trades cryptocurrency.  
  
As of now, it only support Coinbase (most widely available crypto exchange) spot trading. CoinbaseAPI.h is a file which implements and handles the programmatic interaction with Coinbase's Advanced Trade API. It searches your path variables for the public API key tied to your account, and a secret.pem file which holds your secret one.  
  
I wrap the coinbaseAPI with an account manager, which includes my built in risk management system, allowing Meka to trade and bankroll manage an account. The bankroll management is designed to flatten the curve on losing streaks and exponentially increase profits on winning streaks. This is done through adjusting risk after trades. The downside is, this form of bankroll management requires leverage is bind the account to one trade at a time.  
    
# Crypto Pipeline  
I built an overkill pipeline to stream crypto data. This is where my system started, just as a pipeline to recieve, parse, and store live data.  
  
It uses Coinbase's websockets, and is multithreaded for more throughput. The pipeline follows the order:  
Websocket -> Parser -> Aggregator -> (async logger/database)  
  
I've managed to lower the latency from ~500miliseconds to ~80microseconds. I am using very quick lock free queues around 4 threads for the pipeline, but ultimately don't need this much speed/throughput.  
  
# Backtester  
To test strategies for Meka, I first built a backtester which will run trading stragies through years worth of historical data. This part of my system downloads historical candle data from Binance. It also simulates the bankroll management that Meka will use. The backtester does not simulate off of actual fills, it just assumes that it will get the fill. I might change this in the future, or might not. Haven't decided yet.  
  
# Compatibility  
Windows and Linux supported.
