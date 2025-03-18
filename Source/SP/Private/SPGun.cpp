#include "SPGun.h"

AGun::AGun()
{
    MaxAmmo = 30;
    CurrentAmmo = MaxAmmo; // ź���� �ִ�ġ�� �ƴ� ��쿡�� ������
}

void AGun::Reload()
{
    CurrentAmmo = MaxAmmo;
    UE_LOG(LogTemp, Warning, TEXT("Reloaded! Current Ammo: %d"), CurrentAmmo);
}


void AGun::Pickup(AActor* NewOwner) //New
{
    SetOwner(NewOwner); // ���� �����ڸ� ����
    AttachToComponent(NewOwner->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale); // �����ڿ� ����
    UE_LOG(LogTemp, Warning, TEXT("Picked up by: %s"), *NewOwner->GetName());
} //New