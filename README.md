┌────────────────────────┐
│      WebSocket In      │
│  (real-time data feed) │
└─────────────┬──────────┘
              │ raw JSON / tick data
              ▼
┌────────────────────────┐
│        Parser           │
│  - validate message     │
│  - extract fields       │
│  - convert types        │
└─────────────┬──────────┘
              │ normalized tick struct
              ▼
┌────────────────────────┐
│      Aggregator        │
│ - build candles        │
│ - track OHLC           │
│ - time window buckets  │
│ - output events        │
└─────────────┬──────────┘
              │ finished candle
              ▼
┌────────────────────────┐
│      SQL Storage       │
│  - insert/update rows  │
│  - durable history     │
└─────────────┬──────────┘
              │
              ▼
          UI / Chart