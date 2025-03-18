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