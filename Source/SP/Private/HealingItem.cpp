#include "HealingItem.h"
#include "SPCharacter.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ASPCharacter* PlayerCharacter = Cast<ASPCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}
		
		DestroyItem();
	}
}