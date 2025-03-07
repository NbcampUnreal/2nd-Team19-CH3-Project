#include "SmallCoinItem.h"

ASmallCoinItem::ASmallCoinItem()
{
	CoinValue = 10; //강의에선 PointValue = 10; 으로 되어있음
	ItemType = "SmallCoin";
}

void ASmallCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}