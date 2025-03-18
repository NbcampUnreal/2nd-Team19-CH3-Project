#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.h"
#include "SPEnemy.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class SP_API ASpawnVolume : public AActor
{
    GENERATED_BODY()

public:
    ASpawnVolume();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ItemDataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TSubclassOf<ASPEnemy> DefaultEnemyClass;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    AActor* SpawnEnemy();

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    AActor* SpawnRandomItem();

    virtual void BeginPlay() override;

protected:
    FItemSpawnRow* GetRandomItem() const;
    AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
    FVector GetRandomPointInVolume() const;

private:
    FTimerHandle SpawnTimerHandle;
    FTimerHandle StopSpawnTimerHandle;
};