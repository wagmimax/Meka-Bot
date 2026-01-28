#pragma once
#include "Pipeline/ConcurrentQueue.h"
#include <sqlite3.h>
#include "Pipeline/Parser.h"

class Database
{
public:
    void initDB(const std::vector<std::string>&);
    void writeData(CandleData);
    void readData();
private:
    sqlite3* db;
};
