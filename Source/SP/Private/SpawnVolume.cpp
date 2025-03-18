#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "SPEnemy.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

ASpawnVolume::ASpawnVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);

    ItemDataTable = nullptr;
}

void ASpawnVolume::BeginPlay()
{
    Super::BeginPlay();
}

AActor* ASpawnVolume::SpawnEnemy()
{
    if (!DefaultEnemyClass) return nullptr;

    UWorld* World = GetWorld();
    if (!World) return nullptr;

    FVector SpawnLocation = GetRandomPointInVolume();
    SpawnLocation.Z = 0;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ASPEnemy* NewEnemy = World->SpawnActor<ASPEnemy>(DefaultEnemyClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (NewEnemy)
    {
        UE_LOG(LogTemp, Warning, TEXT("Enemy Spawned at %s"), *SpawnLocation.ToString());
        return NewEnemy;
    }
    return nullptr;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
    if (!SpawningBox) return GetActorLocation();

    FVector Origin = SpawningBox->GetComponentLocation();
    FVector Extent = SpawningBox->GetScaledBoxExtent();
    return FMath::RandPointInBox(FBox::BuildAABB(Origin, Extent));
}

AActor* ASpawnVolume::SpawnRandomItem()
{
    if (FItemSpawnRow* SelectedRow = GetRandomItem())
    {
        if (UClass* ActualClass = SelectedRow->ItemClass.Get())
        {
            return SpawnItem(ActualClass);
        }
    }
    return nullptr;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
    if (!ItemDataTable) return nullptr;

    TArray<FItemSpawnRow*> AllRows;
    static const FString ContextString(TEXT("ItemSpawnContext"));
    ItemDataTable->GetAllRows(ContextString, AllRows);

    if (AllRows.IsEmpty()) return nullptr;

    float TotalChance = 0.0f;
    for (const FItemSpawnRow* Row : AllRows)
    {
        if (Row)
        {
            TotalChance += Row->Spawnchance;
        }
    }

    const float RandValue = FMath::FRandRange(0.0f, TotalChance);
    float AccumulateChance = 0.0f;
    for (FItemSpawnRow* Row : AllRows)
    {
        AccumulateChance += Row->Spawnchance;
        if (RandValue <= AccumulateChance)
        {
            return Row;
        }
    }

    return nullptr;
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
    if (!ItemClass) return nullptr;

    UWorld* World = GetWorld();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AActor* SpawnedActor = World->SpawnActor<AActor>(
        ItemClass,
        GetRandomPointInVolume(),
        FRotator::ZeroRotator,
        SpawnParams
    );
    return SpawnedActor;
}