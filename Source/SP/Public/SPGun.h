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
    void Reload();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    int32 MaxAmmo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
    int32 CurrentAmmo;
};