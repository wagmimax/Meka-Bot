#pragma once
#include <ConcurrentQueue.h>
#include <sqlite3.h>
#include <Parser.h>

class Database
{
public:
    void initDB(const std::vector<std::string>&);
    void writeData(CandleData);
    void readData();
private:
    sqlite3* db;
};
