#include "FirstGameInstance.h"

UFirstGameInstance::UFirstGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void UFirstGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated: %d"), TotalScore);
}