┌────────────────────────┐
│      WebSocket In      │
│  (real-time data feed) │
└─────────────┬──────────┘
              │ raw JSON
              ▼
┌────────────────────────┐
│        Parser          │
│  - extract fields      │
│  - convert types       │
│  - push data into queue│
└─────────────┬──────────┘
              │ candle data
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