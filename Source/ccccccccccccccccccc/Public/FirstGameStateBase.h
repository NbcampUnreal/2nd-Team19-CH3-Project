#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FirstGameStateBase.generated.h"

UCLASS()
class SECONDPROJECT_API AFirstGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AFirstGameStateBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);
};
