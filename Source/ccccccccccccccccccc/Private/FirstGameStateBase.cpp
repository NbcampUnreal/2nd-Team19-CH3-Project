#include "FirstGameStateBase.h"

AFirstGameStateBase::AFirstGameStateBase()
{
	Score = 0;
}

int32 AFirstGameStateBase::GetScore() const
{
	return Score;
}

void AFirstGameStateBase::AddScore(int32 Amount)
{
	Score += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), Score);
}