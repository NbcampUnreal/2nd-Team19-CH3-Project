#include "SmallCoinItem.h"

ASmallCoinItem::ASmallCoinItem()
{
	CoinValue = 10; //���ǿ��� PointValue = 10; ���� �Ǿ�����
	ItemType = "SmallCoin";
}

void ASmallCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}