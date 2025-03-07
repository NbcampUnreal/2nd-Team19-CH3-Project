#include "FirstGameState.h"
#include "FirstGameInstance.h"
#include "MyPlayerController.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AFirstGameState::AFirstGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void AFirstGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AFirstGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 AFirstGameState::GetScore() const
{
	return Score;
}

void AFirstGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UFirstGameInstance* FirstGameInstance = Cast<UFirstGameInstance>(GameInstance);
		if (FirstGameInstance)
		{
			FirstGameInstance->AddToScore(Amount);
		}
	}
}

void AFirstGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* FirstPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			FirstPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UFirstGameInstance* FirstGameInstance = Cast<UFirstGameInstance>(GameInstance);
		if (FirstGameInstance)
		{
			CurrentLevelIndex = FirstGameInstance->CurrentLevelIndex;
		}
	}

	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;

	for (int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
			
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AFirstGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);

}

void AFirstGameState::OnLevelTimeUp()
{
	EndLevel();
}

void AFirstGameState::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount);

		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
		{
			EndLevel();
		}
}

void AFirstGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
    CurrentLevelIndex++;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UFirstGameInstance* FirstGameInstance = Cast<UFirstGameInstance>(GameInstance);
		if (FirstGameInstance)
		{
			AddScore(Score);
		    CurrentLevelIndex++;
            FirstGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void AFirstGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* FirstPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			FirstPlayerController->SetPause(true);
			FirstPlayerController->ShowMainMenu(true);
		}
	}
}

void AFirstGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = MyPlayerController->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						UFirstGameInstance* FirstGameInstance = Cast<UFirstGameInstance>(GameInstance);
						if (FirstGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), FirstGameInstance->TotalScore)));
						}
					}
				}

				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
				}
			}
		}
	}
}