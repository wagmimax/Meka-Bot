#pragma once

#include "PaperAccount.h"
#include "Strategy.h"
#include <fstream>
#include <sstream>
#include <iomanip>

class Backtester
{
public:
    void run(Strategy& strategy);

private:
    PaperAccount paperAccount;
};