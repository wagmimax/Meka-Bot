import win32pipe
import win32file

def read_pipe_data_buffered():
    pipe_name = r'\\.\pipe\dataPipe'
    buffer = ""
    
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
                    if len(parts) == 7:
                        ticker, o, h, l, c, vol, ts = parts
                        print(f"Candle: {ticker} O:{o} H:{h} L:{l} C:{c} V:{vol} T:{ts}")
            else:
                print("Error reading data: " + result)
                        
    except Exception as e:
        print(f"Error: {e}")

read_pipe_data_buffered()