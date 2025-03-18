#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPWeapon.generated.h"

UCLASS()
class SP_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon(); // 생성자: 무기 객체가 생성될 때 호출되는 함수

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire(); // 발사 기능: 무기를 발사하는 함수


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float DamageAmount; // 무기 데미지: 무기가 입히는 데미지 양

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float WeaponRange; // 무기 사거리: 무기가 공격할 수 있는 최대 거리

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootComp; // 루트 컴포넌트: 무기의 기본 위치를 정의하는 컴포넌트

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WeaponMesh; // 무기 메시: 무기의 3D 모델을 나타내는 컴포넌트
};