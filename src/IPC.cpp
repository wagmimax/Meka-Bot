#include<IPC.h>
#include<sstream>

int NamedPipe::createConnection()
{
    hPipe = CreateNamedPipeW(L"\\\\.\\pipe\\dataPipe",
        PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 
        1, 1024, 1024, 0, NULL);

    if(hPipe == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error making pipe: " << GetLastError();
        return -1;
    }
     
    Connected = ConnectNamedPipe(hPipe, NULL);
    system("python ../../../src/Charting.py"); //start up other process, which will be client

    if(!Connected) CloseHandle(hPipe);
    else std::cout << "Pipe connected\n";
    
    return 1;
}

void NamedPipe::sendData()
{
    CandleData currentCandle;
    std::stringstream message;
    DWORD bytesWritten;

    while(true)
    {
        currentCandle = candleData.popValue();
        message << currentCandle.ticker << " " 
                << currentCandle.open << " "
                << currentCandle.high << " " 
                << currentCandle.low << " "
                << currentCandle.close << " "
                << currentCandle.volume << " "
                << currentCandle.timestamp << "\n";
        std::string messageOut = message.str();

        WriteFile(hPipe, messageOut.c_str(), messageOut.size(), &bytesWritten, NULL); 

        message.str("");
        message.clear();
    }
    
}