#pragma once

#include "CoreMinimal.h"
#include "SPWeapon.h"
#include "SPGun.generated.h"

UCLASS()
class SP_API AGun : public AWeapon
{
    GENERATED_BODY()

public:
    AGun();

    UFUNCTION(BlueprintCallable, Category = "Gun")
    void Reload(); // 재장전 기능 추가

    UFUNCTION(BlueprintCallable, Category = "Gun") //New
    void Pickup(AActor* NewOwner); // 총을 획득하는 기능 추가 New

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    int32 MaxAmmo; // 최대 탄약 수

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
    int32 CurrentAmmo; // 현재 탄약 수
};