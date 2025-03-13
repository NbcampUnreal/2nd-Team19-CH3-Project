#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPEnemy.generated.h"

UCLASS()
class SP_API ASPEnemy : public AActor
{
    GENERATED_BODY()

public:
    ASPEnemy();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Health;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* EnemyMesh;

    virtual void BeginPlay() override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    void OnDeath();
};