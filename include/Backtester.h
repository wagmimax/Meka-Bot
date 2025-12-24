#include "PaperAccount.h"
#include "Strategy.h"

class Backtester
{
public:

    void run(Strategy& strategy);

private:
    PaperAccount paperAccount;
};