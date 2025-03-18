#include "SPWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

AWeapon::AWeapon()
{
    PrimaryActorTick.bCanEverTick = false; // 이 액터는 틱(매 프레임 업데이트)을 사용하지 않음

    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")); // 루트 컴포넌트 생성
    SetRootComponent(RootComp); // 루트 컴포넌트 설정

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));// 무기 메시 컴포넌트 생성
    WeaponMesh->SetupAttachment(RootComp); // 무기 메시를 루트 컴포넌트에 부착

    DamageAmount = 20.0f; // 무기의 기본 데미지 설정
    WeaponRange = 10000.0f; // 무기의 사거리 설정
}

void AWeapon::Fire()
{
    FVector StartLocation = GetOwner()->GetActorLocation(); // 무기를 소유한 액터의 위치
    FVector ForwardVector = GetOwner()->GetActorForwardVector(); // 무기를 소유한 액터의 전방 벡터
    FVector EndLocation = StartLocation + (ForwardVector * WeaponRange); // 무기의 사거리 끝 위치 계산

    FCollisionQueryParams QueryParams; // 충돌 검색을 위한 파라미터
    QueryParams.AddIgnoredActor(this); // 무기 자신은 충돌 검색에서 제외
    QueryParams.AddIgnoredActor(GetOwner()); // 무기를 소유한 액터도 충돌 검색에서 제외
    QueryParams.bTraceComplex = true; // 복잡한 충돌 검색 사용

    FHitResult HitResult; // 충돌 결과를 저장할 변수
    bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams); // 라인 트레이스 실행
    if (bIsHit) // 충돌이 발생한 경우
    {
        AActor* HitActor = HitResult.GetActor(); // 충돌한 액터 가져오기
		if (HitActor) // 충돌한 액터가 유효한 경우
        {
			FDamageEvent DamageEvent; // 데미지 이벤트 생성
            HitActor->TakeDamage(DamageAmount, DamageEvent, nullptr, this); // 충돌한 액터에 데미지 적용
            UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s, Applied Damage: %.1f"), *HitActor->GetName(), DamageAmount); // 로그 출력
        }

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 16, FColor::Green, false, 2.0f); // 충돌 지점에 디버그 스피어 그리기
        DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, FColor::Green, false, 2.0f, 0, 1.0f); // 시작 지점부터 충돌 지점까지 디버그 라인 그리기
    }
    else // 충돌이 발생하지 않은 경우
    {
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 2.0f, 0, 1.0f); // 시작 지점부터 끝 지점까지 디버그 라인 그리기
    }
}