#include "SPGameState.h"
#include "SPGameInstance.h"
#include "SPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

ASPGameState::ASPGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
	SpawnedEnemyCount = 5;
	DestroyEmenyCount = 0;
}

void ASPGameState::BeginPlay()
{
	Super::BeginPlay();
	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ASPGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 ASPGameState::GetScore() const
{
	return Score;
}

void ASPGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USPGameInstance* SPGameInstance = Cast<USPGameInstance>(GameInstance);
		if (SPGameInstance)
		{
			SPGameInstance->AddToScore(Amount);
		}
	}
}

void ASPGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASPPlayerController* SPPlayerController = Cast<ASPPlayerController>(PlayerController))
		{
			SPPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USPGameInstance* SPGameInstance = Cast<USPGameInstance>(GameInstance);
		if (SPGameInstance)
		{
			CurrentLevelIndex = SPGameInstance->CurrentLevelIndex;
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
		&ASPGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);

	UpdateHUD();
	GenerateEnemy();

	UpdateHUD();

	UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d coin"),
		CurrentLevelIndex + 1,
		SpawnedCoinCount);
}

void ASPGameState::OnEnemyDestroyed()
{
	DestroyEmenyCount++;

	UE_LOG(LogTemp, Warning, TEXT("Enemy Destroyed: %d / %d"), SpawnedEnemyCount, DestroyEmenyCount)
		if (SpawnedEnemyCount > 0 && DestroyEmenyCount >= SpawnedEnemyCount)
		{
			GenerateEnemy();
		}
}

void ASPGameState::GenerateEnemy()
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for (int32 i = 0; i < SpawnedEnemyCount; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnEnemy();
			}
		}
	}
}


void ASPGameState::OnLevelTimeUp()
{
	EndLevel();
}

void ASPGameState::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount)

		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
		{
			EndLevel();
		}
}

void ASPGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USPGameInstance* SPGameInstance = Cast<USPGameInstance>(GameInstance);
		if (SPGameInstance)
		{
			AddScore(Score);
			CurrentLevelIndex++;
			SPGameInstance->CurrentLevelIndex = CurrentLevelIndex;
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

void ASPGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASPPlayerController* SPPlayerController = Cast<ASPPlayerController>(PlayerController))
		{
			SPPlayerController->ShowMainMenu(true);
		}
	}
}

void ASPGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASPPlayerController* SPPlayerController = Cast<ASPPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = SPPlayerController->GetHUDWidget())
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
						USPGameInstance* SPGameInstance = Cast<USPGameInstance>(GameInstance);
						if (SPGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SPGameInstance->TotalScore)));
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