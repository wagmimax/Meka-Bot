WIP

Meka Bot (will be) a fully automatic trading bot, capable of executing strategies and safely handling bankroll

My program features three parts:  
  
- Meka Bot  
Meka will follow strict risk management, safely handling even leveraged accounts.  
It will trade crypto currency using Coinbase's advanced trade API, through REST endpoints.  
  
- Realtime Data Pipeline
Meka needs food, and that food is data. That's why a pipeline is needed.  
Coinbase websocket is used to receive raw trade data. That data is parsed and aggregated into 1m candles.  
The pipeline is multithreaded and a bit heavy on resources. It also features IPC with python for data visualization.  
  
- Strategy Backtester
Meka will execute based off algorithmic strategies, and the backtester is here to test those strategies.  
The backtester will download and test on Binance's historical candle data. Downloaded assets are automatically cleaned up.  
It is assumed that leverage exists, and is necessary for the bankroll management that Meka and the Backtester will follow.  