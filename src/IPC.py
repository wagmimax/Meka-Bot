import win32pipe
import win32file
import pandas as pd
import numpy as np
import mplfinance as mpf
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import finplot as fplt
import yfinance
import threading
from datetime import datetime, timedelta
import random

candlesBTC = []
candles_lock = threading.Lock()

def read_pipe():
    pipe_name = r'\\.\pipe\dataPipe'
    buffer = ""
    

    #read live data
    try:
        pipe_handle = win32file.CreateFile(
            pipe_name, win32file.GENERIC_READ, 0, None,
            win32file.OPEN_EXISTING, 0, None
        )
        
        print("Connected to pipe")
        
        while True:
            result, data = win32file.ReadFile(pipe_handle, 1024)
            if result == 0:
                buffer += data.decode('utf-8')
                
                # Process complete lines
                while '\n' in buffer:
                    line, buffer = buffer.split('\n', 1)
                    parts = line.strip().split()
                    if len(parts) == 8:
                        ticker, o, h, l, c, vol, ts, min = parts
                        o, h, l, c = float(o), float(h), float(l), float(c)
                        try:
                            dt = datetime.fromisoformat(ts[0:19])
                            timestamp = dt.timestamp()
                            #print(ts)
                        except ValueError as e:
                            print(f"Timestamp parse error: {e}, skipping")
                            continue
                        #2025-12-13T02:58:53.152515Z
                        if ticker != 'BTC':
                            continue
                        with candles_lock:
                            #if candles is empty, append the current candle
                            if len(candlesBTC) == 0 and ticker == 'BTC':
                                candlesBTC.append({'Open':o,
                                            'High':h,
                                            'Low':l,
                                            'Close':c,
                                            'Time':timestamp,
                                            'Min':min})
                            #if the minute is different, append the new candle
                            elif not (candlesBTC[-1]['Min'] == min) and ticker == 'BTC':
                                candlesBTC.append({'Open':o,
                                            'High':h,
                                            'Low':l,
                                            'Close':c,
                                            'Time':timestamp,
                                            'Min':min})
                            elif ticker == 'BTC':
                                #update current candle 
                                candlesBTC[-1]['Open'] = o
                                candlesBTC[-1]['High'] = h
                                candlesBTC[-1]['Low'] = l
                                candlesBTC[-1]['Close'] = c
                            
                        #print(f"Candle: {ticker} O:{o} H:{h} L:{l} C:{c} V:{vol} T:{ts} M:{min}")         
            else:
                print("Error reading data: " + result)
    except Exception as e:
        print(f"Error: {e}")

pipe_thread = threading.Thread(target=read_pipe, daemon=True)
pipe_thread.start()

def update_chart():
        with candles_lock:
            if len(candlesBTC) == 0:
                return
            df = pd.DataFrame(candlesBTC)

        ax.clear()
        fplt.candlestick_ochl(df[['Time', 'Open', 'Close', 'High', 'Low']], ax=ax)
        fplt.refresh()

ax = fplt.create_plot('BTC Chart', init_zoom_periods=30)

# Set up timer to update chart periodically
fplt.timer_callback(update_chart, 0.1)  # Update every 1 second

# Show plot (blocking - keeps main thread alive)
fplt.show()