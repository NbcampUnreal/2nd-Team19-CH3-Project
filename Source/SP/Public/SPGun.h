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
    void Reload(); // ������ ��� �߰�

    UFUNCTION(BlueprintCallable, Category = "Gun") //New
    void Pickup(AActor* NewOwner); // ���� ȹ���ϴ� ��� �߰� New

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    int32 MaxAmmo; // �ִ� ź�� ��

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
    int32 CurrentAmmo; // ���� ź�� ��
};