#include "CoinItem.h"
#include "Engine/World.h"
#include "FirstGameStateBase.h"

ACoinItem::ACoinItem()
{
	CoinValue = 0; //���ǿ��� PointValue�� �Ǿ�����
    ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
		if (UWorld* World = GetWorld())
		{
			if (AFirstGameStateBase* GameState = World->GetGameState<AFirstGameStateBase>())
			{
				GameState->AddScore(CoinValue); //���ǿ��� PointValue�� �Ǿ�����
			}
		}
            DestroyItem();
    }
}