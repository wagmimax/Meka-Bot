#include<PaperAccount.h>

void PaperAccount::enterPosition(Trade trade)
{
    double riskAmount = (double{2} / 100) * balance_;
    double positionSize = riskAmount / (trade.stopLossPercent + (makerFees_ + takerFees_));
    double finalPosition = positionSize * leverage_;
}