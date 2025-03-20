#include "SPSpawnEnemy.h"
#include "Components/BoxComponent.h"
#include "SPEnemy.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"

ASPSpawnEnemy::ASPSpawnEnemy()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);

    SpawningBox->SetCollisionProfileName(TEXT("Trigger"));
    SpawningBox->SetGenerateOverlapEvents(true);

    SpawnInterval = 5.0f;
    SpawnDuration = 60.0f;
    MaxEnemies = 10;
    CurrentEnemies = 0;
}

void ASPSpawnEnemy::BeginPlay()
{
    Super::BeginPlay();

    SpawningBox->OnComponentBeginOverlap.AddDynamic(this, &ASPSpawnEnemy::OnOverlapBegin);

    StartSpawning();
}

void ASPSpawnEnemy::StartSpawning()
{
    float RandomInterval = FMath::RandRange(3.0f, 8.0f); // 3초에서 8초 사이 랜덤 간격
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASPSpawnEnemy::SpawnEnemy, RandomInterval, true);
    OnSpawningStarted.Broadcast();
}

void ASPSpawnEnemy::StopSpawning()
{
    GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
    UE_LOG(LogTemp, Warning, TEXT("Spawning Stopped!"));
    OnSpawningStopped.Broadcast();
}

void ASPSpawnEnemy::SpawnEnemy()
{
    if (CurrentEnemies < MaxEnemies && EnemyClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FVector SpawnLocation = GetRandomPointInVolume();
            FRotator SpawnRotation = FRotator::ZeroRotator;

            ASPEnemy* NewEnemy = World->SpawnActor<ASPEnemy>(EnemyClass, SpawnLocation, SpawnRotation);
            if (NewEnemy)
            {
                CurrentEnemies++;
                UE_LOG(LogTemp, Warning, TEXT("Enemy Spawned! Current Enemies: %d"), CurrentEnemies);
            }
        }
    }
}

FVector ASPSpawnEnemy::GetRandomPointInVolume() const
{
    if (SpawningBox)
    {
        FVector Origin = SpawningBox->GetComponentLocation();
        FVector Extent = SpawningBox->GetScaledBoxExtent();
        return FMath::RandPointInBox(FBox::BuildAABB(Origin, Extent));
    }
    return GetActorLocation();
}

void ASPSpawnEnemy::OnEnemyDestroyed()
{
    CurrentEnemies--;
}

void ASPSpawnEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
    if (PlayerCharacter)
    {
        float DamageAmount = 10.0f;
        FDamageEvent DamageEvent;
        PlayerCharacter->TakeDamage(DamageAmount, DamageEvent, nullptr, this);

        UE_LOG(LogTemp, Warning, TEXT("Player took damage!"));
    }
}