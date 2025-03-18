#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class AWeapon;

UCLASS()
class SP_API ASPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASPCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeapon* CurrentWeapon;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeapon> DefaultWeaponClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;


	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);
	
	
	UFUNCTION()
	void BeginCrouch(const FInputActionValue& value);
	UFUNCTION()
	void EndCrouch(const FInputActionValue& value);
	

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(AWeapon* WeaponToEquip);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireWeapon();

public: //New
	ASPCharacter();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PickupWeapon(AGun* Weapon); // ÃÑÀ» È¹µæÇÏ´Â ±â´É Ãß°¡New

public: //New
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); //New
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireWeapon(); // ÃÑ ¹ß»ç ±â´É Ãß°¡ New

protected: //New
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AGun* CurrentWeapon; // ÇöÀç ¼ÒÀ¯ÇÑ ÃÑ //New

private:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
};
