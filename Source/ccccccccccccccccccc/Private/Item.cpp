#include "Item.h"



AItem::AItem()
{
	SceneRoot = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateEditorOnlyDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Potion_A.SM_Potion_A"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Heart.M_Heart"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;
		RotationSpeed = 90.f;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	SetActorScale3D(FVector(2.0f));
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0F, RotationSpeed, 0.0f));
	}

}

// 생성자 - 메모리에 생김. 딱 한번 호출.
// PostInitializeComponents() - 컴포넌트가 완성된 직후 호출. 컴포넌트끼리 데이터 주고받기, 상호작용
// BeginPlay() - 배치 (Spawn) 직후
// Tick(float DeltaTime) - 매 프레임마다 호출됨.
// Destoyed() - 삭제 되기 직전에 호출된다.
// EndPlay() - 게임 종료, 파괴 (Destroyed()), 레벨 전환
