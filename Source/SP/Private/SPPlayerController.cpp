#include "SPPlayerController.h"
#include "SPGameState.h"
#include "SPGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include <SPGameMode.cpp> //New

ASPPlayerController::ASPPlayerController()
	:InputMappingContext(nullptr),
	 MoveAction(nullptr),
	 JumpAction(nullptr),
	 LookAction(nullptr),
	 SprintAction(nullptr),
	 CrouchAction(nullptr),
	 HUDWidgetClass(nullptr),
	 HUDWidgetInstance(nullptr),
	 MainMenuWidgetClass(nullptr),
	 MainMenuWidgetInstance(nullptr)
{
}

void ASPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MainLevel"))
	{
		ShowMainMenu(false);
	}
}

UUserWidget* ASPPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ASPPlayerController::ShowMainMenu(bool bIsRestart)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}
	}
}

void ASPPlayerController::ShowGameHUD()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());

			ASPGameState* SPGameState = GetWorld() ? GetWorld()->GetGameState<ASPGameState>() : nullptr;
			if (SPGameState)
			{
				SPGameState->UpdateHUD();
			}
		}
	}
}

void ASPPlayerController::StartGame()
{
	if (USPGameInstance* SPGameInstance = Cast<USPGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		SPGameInstance->CurrentLevelIndex = 0;
		SPGameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
}

void ASPPlayerController::SetupInputComponent() //New
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Fire", IE_Pressed, this, &ASPPlayerController::OnFire);
}

void ASPPlayerController::OnFire()
{
	if (ASPCharacter* Character = Cast<ASPCharacter>(GetPawn()))
	{
		Character->FireWeapon(); // รั น฿ป็
	}
} //New