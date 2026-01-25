#include<ConcurrentQueue.h>

ConcurrentQueue<TimestampedMessage> rawData;
ConcurrentQueue<TradeData> tradeData;
ConcurrentQueue<CandleData> candleData;
ConcurrentQueue<LoggerFormat> logs;