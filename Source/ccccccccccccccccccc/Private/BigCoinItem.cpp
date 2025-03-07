#include "BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
	CoinValue = 50; //강의에선 PointValue = 50; 으로 되어있음
	ItemType = "BigCoin";
}

void ABigCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}