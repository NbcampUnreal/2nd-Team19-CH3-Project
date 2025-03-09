#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FirstGameInstance.generated.h"

UCLASS()
class CCCCCCCCCCCCCCCCCCC_API UFirstGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFirstGameInstance();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
};
