#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPEnemy.h"
#include "SPSpawnEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawningStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawningStopped);

class UBoxComponent;

UCLASS()
class SP_API ASPSpawnEnemy : public AActor
{
    GENERATED_BODY()

public:
    ASPSpawnEnemy();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    UBoxComponent* SpawningBox;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TSubclassOf<ASPEnemy> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float SpawnInterval;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float SpawnDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    int32 MaxEnemies;

    UPROPERTY(BlueprintAssignable, Category = "Spawning")
    FOnSpawningStarted OnSpawningStarted;

    UPROPERTY(BlueprintAssignable, Category = "Spawning")
    FOnSpawningStopped OnSpawningStopped;

protected:
    virtual void BeginPlay() override;

public:
    void OnEnemyDestroyed();

private:
    FTimerHandle SpawnTimerHandle;
    FTimerHandle StopSpawnTimerHandle;

    int32 CurrentEnemies;

    void StartSpawning();
    void StopSpawning();
    void SpawnEnemy();
    FVector GetRandomPointInVolume() const;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};