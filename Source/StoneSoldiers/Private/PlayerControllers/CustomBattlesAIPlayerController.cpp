/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "PlayerControllers/CustomBattlesAIPlayerController.h"

bool ACustomBattlesAIPlayerController::SwapToGameplayInteractionOptionsUI()
{
	return Super::SwapToGameplayInteractionOptionsUI();
}

bool ACustomBattlesAIPlayerController::SwapToDefaultInGameUI()
{
	return SwapToGameplayInteractionOptionsUI();
}

void ACustomBattlesAIPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
