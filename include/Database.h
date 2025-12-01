#include <ConcurrentQueue.h>
#include <sqlite3.h>
#include <Parser.h>

void initTables(std::vector<std::string>&);
void writeData(CandleData);
void readData();