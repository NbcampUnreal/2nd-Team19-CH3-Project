#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPWeapon.generated.h"

UCLASS()
class SP_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon(); // ������: ���� ��ü�� ������ �� ȣ��Ǵ� �Լ�

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire(); // �߻� ���: ���⸦ �߻��ϴ� �Լ�


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float DamageAmount; // ���� ������: ���Ⱑ ������ ������ ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float WeaponRange; // ���� ��Ÿ�: ���Ⱑ ������ �� �ִ� �ִ� �Ÿ�

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootComp; // ��Ʈ ������Ʈ: ������ �⺻ ��ġ�� �����ϴ� ������Ʈ

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WeaponMesh; // ���� �޽�: ������ 3D ���� ��Ÿ���� ������Ʈ
};