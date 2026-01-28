#include<Windows.h>
#include"Pipeline/ConcurrentQueue.h"
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