#include "SPWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

AWeapon::AWeapon()
{
    PrimaryActorTick.bCanEverTick = false; // �� ���ʹ� ƽ(�� ������ ������Ʈ)�� ������� ����

    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")); // ��Ʈ ������Ʈ ����
    SetRootComponent(RootComp); // ��Ʈ ������Ʈ ����

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));// ���� �޽� ������Ʈ ����
    WeaponMesh->SetupAttachment(RootComp); // ���� �޽ø� ��Ʈ ������Ʈ�� ����

    DamageAmount = 20.0f; // ������ �⺻ ������ ����
    WeaponRange = 10000.0f; // ������ ��Ÿ� ����
}

void AWeapon::Fire()
{
    FVector StartLocation = GetOwner()->GetActorLocation(); // ���⸦ ������ ������ ��ġ
    FVector ForwardVector = GetOwner()->GetActorForwardVector(); // ���⸦ ������ ������ ���� ����
    FVector EndLocation = StartLocation + (ForwardVector * WeaponRange); // ������ ��Ÿ� �� ��ġ ���

    FCollisionQueryParams QueryParams; // �浹 �˻��� ���� �Ķ����
    QueryParams.AddIgnoredActor(this); // ���� �ڽ��� �浹 �˻����� ����
    QueryParams.AddIgnoredActor(GetOwner()); // ���⸦ ������ ���͵� �浹 �˻����� ����
    QueryParams.bTraceComplex = true; // ������ �浹 �˻� ���

    FHitResult HitResult; // �浹 ����� ������ ����
    bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams); // ���� Ʈ���̽� ����
    if (bIsHit) // �浹�� �߻��� ���
    {
        AActor* HitActor = HitResult.GetActor(); // �浹�� ���� ��������
		if (HitActor) // �浹�� ���Ͱ� ��ȿ�� ���
        {
			FDamageEvent DamageEvent; // ������ �̺�Ʈ ����
            HitActor->TakeDamage(DamageAmount, DamageEvent, nullptr, this); // �浹�� ���Ϳ� ������ ����
            UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s, Applied Damage: %.1f"), *HitActor->GetName(), DamageAmount); // �α� ���
        }

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 16, FColor::Green, false, 2.0f); // �浹 ������ ����� ���Ǿ� �׸���
        DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, FColor::Green, false, 2.0f, 0, 1.0f); // ���� �������� �浹 �������� ����� ���� �׸���
    }
    else // �浹�� �߻����� ���� ���
    {
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 2.0f, 0, 1.0f); // ���� �������� �� �������� ����� ���� �׸���
    }
}