#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "Components/SphereComponent.h" //�� �κ��� ���ǿ� ����
#include "BaseItem.generated.h"

class USceneComponent;

UCLASS()
class SECONDPROJECT_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()

public:
	ABaseItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Component")

	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Component")

	USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Component")

	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* PickupParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* PickupSound;

	virtual void OnItemOverlap(
	    UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;

	virtual void DestroyItem();
};