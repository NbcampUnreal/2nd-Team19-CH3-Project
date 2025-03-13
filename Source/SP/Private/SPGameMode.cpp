#include "SPGameMode.h"
#include "SPCharacter.h"
#include "SPPlayerController.h"
#include "SPGameState.h"

ASPGameMode::ASPGameMode()
{
	DefaultPawnClass = ASPCharacter::StaticClass();
	PlayerControllerClass = ASPPlayerController::StaticClass();
	GameStateClass = ASPGameState::StaticClass();
}