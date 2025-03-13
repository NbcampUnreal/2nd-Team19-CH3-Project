#include "SPEnemy.h"
#include "SPGameState.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ASPEnemy::ASPEnemy()
{
    PrimaryActorTick.bCanEverTick = false;

    EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
    SetRootComponent(EnemyMesh);

    EnemyMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    Health = 100.f;
}

void ASPEnemy::BeginPlay()
{
    Super::BeginPlay();
}

float ASPEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    Health -= ActualDamage;

    if (Health <= 0.0f)
    {
        OnDeath();
    }

    return ActualDamage;
}

void ASPEnemy::OnDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy destroyed!"));
    Destroy();

    if (UWorld* World = GetWorld())
    {
        if (ASPGameState* GameState = World->GetGameState<ASPGameState>())
        {
            GameState->OnEnemyDestroyed();
        }
    }
}