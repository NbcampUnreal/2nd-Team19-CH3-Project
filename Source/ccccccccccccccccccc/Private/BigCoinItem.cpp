#include "BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
	CoinValue = 50; //���ǿ��� PointValue = 50; ���� �Ǿ�����
	ItemType = "BigCoin";
}

void ABigCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}