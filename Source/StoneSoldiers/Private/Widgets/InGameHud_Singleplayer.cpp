/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/InGameHud_Singleplayer.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Components/WidgetSwitcher.h"
#include "PlayerControllers/SS_PlayerController_Singleplayer.h"
#include "Widgets/Components/PreBattleOptions.h"
#include "Widgets/Components/GameplayInteractionOptions.h"
#include "PlayerStates/StoneSoldierPlayerState.h"

bool UInGameHud_Singleplayer::GoToPreBattleOptions()
{
	if (WidgetSwitcher && PreBattleOptions)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		return true;
	}

	StoneSoldiersHelperFunctions::LogEngineMessage("Problem switching to PreBattle | InGameHudSinglePlayer | GoToPreBattleOptions");
	return false;
}

bool UInGameHud_Singleplayer::GoToMainInGameOverlay()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);

		if (ASS_PlayerController_Singleplayer* PC = Cast<ASS_PlayerController_Singleplayer>(GetOwningPlayer()))
		{
			if (AStoneSoldierPlayerState* PlayerState = PC->GetPlayerState<AStoneSoldierPlayerState>())
			{
				PlayerState->GoToStateFromCurrent("My Turn");
			}
			else
			{
				StoneSoldiersHelperFunctions::LogEngineMessage("Cannot retrieve Player State | InGameHudSinglePlayer | GoToMainInGameOverlay");
			}
		}
		else
		{
			StoneSoldiersHelperFunctions::LogEngineMessage("Cannot retrieve PC | InGameHudSinglePlayer | GoToMainInGameOverlay");
		}
		
		return true;
	}
	
	StoneSoldiersHelperFunctions::LogEngineMessage("Problem switching to MainInGameOverlay | InGameHudSinglePlayer | GoToMainInGameOverlay");
	return false;
}

bool UInGameHud_Singleplayer::GoToGameplayInteractionOptions()
{
	if (WidgetSwitcher && GameplayInteractionOptions)
	{
		WidgetSwitcher->SetActiveWidgetIndex(3);
		GameplayInteractionOptions->ReturnToInteractionOptions();
		return true;
	}

	StoneSoldiersHelperFunctions::LogEngineMessage("GoToGameplayInteractionOptions failed! | UInGameHud_Singleplayer");
	
	return false;
}

bool UInGameHud_Singleplayer::Initialize()
{
	if (!Super::Initialize()) return false;
	
	if (PreBattleOptions)
	{
		if (PreBattleOptions->SetParentHUD(this) == false)
			StoneSoldiersHelperFunctions::LogEngineMessage("PreBattleOptions->SetParentHUD() failed | UInGameHud_Singleplayer | Initialize");
	}

	if (GameplayInteractionOptions)
	{
		if (GameplayInteractionOptions->SetParentHUD(this) == false)
			StoneSoldiersHelperFunctions::LogEngineMessage("GameplayInteractionOptions->SetParentHUD() failed | UInGameHud_Singleplayer | Initialize");
	}
	return true;
}
