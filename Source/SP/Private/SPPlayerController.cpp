#include "SPPlayerController.h"
#include "SPGameState.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"

ASPPlayerController::ASPPlayerController()
	:InputMappingContext(nullptr),
	 MoveAction(nullptr),
	 JumpAction(nullptr),
	 LookAction(nullptr),
	 SprintAction(nullptr)
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

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}
	
	ASPGameState* SPGameState = GetWorld() ? GetWorld()->GetGameState<ASPGameState>() : nullptr;
	if (SPGameState)
	{
		SPGameState->UpdateHUD();
	}
}

UUserWidget* ASPPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}