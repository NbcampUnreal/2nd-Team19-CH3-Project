#include "FirstGameMode.h"
#include "FirstCharacter.h"
#include "MyPlayerController.h"
#include "FirstGameStateBase.h"

AFirstGameMode::AFirstGameMode()
{
	DefaultPawnClass = AFirstCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AFirstGameStateBase::StaticClass();
}
