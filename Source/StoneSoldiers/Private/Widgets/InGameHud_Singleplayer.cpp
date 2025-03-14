// ©Van Phan


#include "Widgets/InGameHud_Singleplayer.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/Components/PreBattleOptions.h"

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
		return true;
	}
	StoneSoldiersHelperFunctions::LogEngineMessage("Problem switching to MainInGameOverlay | InGameHudSinglePlayer | GoToMainInGameOverlay");
	return false;
}

bool UInGameHud_Singleplayer::Initialize()
{
	if (!Super::Initialize()) return false;

	
	if (PreBattleOptions)
	{
		
		if (PreBattleOptions->SetParentHUD(this) == false)
		{
			StoneSoldiersHelperFunctions::LogEngineMessage("PreBattleOptions->SetParentHUD() failed | UInGameHud_Singleplayer | Initialize");
		}
		
	}
	return true;
}
