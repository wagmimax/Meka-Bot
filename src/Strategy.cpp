#include <Strategy.h>

Trade SupportResistance::next(CandleData candle)
{
    return Trade{TradeIntent::NONE, -1, -1};
}