#include<Windows.h>
#include<ConcurrentQueue.h>
#include<iostream>

class NamedPipe
{
    public:
        void sendData();

    private:
        int createConnection(); 
        HANDLE hPipe;
        BOOL Connected;
};