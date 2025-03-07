#include "HealingItem.h"
#include "FirstCharacter.h"

AHealingItem::AHealingItem()
{
    HealAmount = 20.0f;
    ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
		if (AFirstCharacter* PlayerCharacter = Cast<AFirstCharacter>(Activator))
        {
            PlayerCharacter->AddHealth(HealAmount);
		}

        DestroyItem();
    }
}