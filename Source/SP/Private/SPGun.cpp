#include "SPGun.h"

AGun::AGun()
{
    MaxAmmo = 30;
    CurrentAmmo = MaxAmmo;
}

void AGun::Reload()
{
    CurrentAmmo = MaxAmmo;
    UE_LOG(LogTemp, Warning, TEXT("Reloaded! Current Ammo: %d"), CurrentAmmo);
}