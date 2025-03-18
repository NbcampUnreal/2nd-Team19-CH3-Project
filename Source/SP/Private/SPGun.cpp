#include "SPGun.h"

AGun::AGun()
{
    MaxAmmo = 30;
    CurrentAmmo = MaxAmmo; // 탄약이 최대치가 아닌 경우에만 재장전
}

void AGun::Reload()
{
    CurrentAmmo = MaxAmmo;
    UE_LOG(LogTemp, Warning, TEXT("Reloaded! Current Ammo: %d"), CurrentAmmo);
}


void AGun::Pickup(AActor* NewOwner) //New
{
    SetOwner(NewOwner); // 총의 소유자를 설정
    AttachToComponent(NewOwner->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale); // 소유자에 부착
    UE_LOG(LogTemp, Warning, TEXT("Picked up by: %s"), *NewOwner->GetName());
} //New