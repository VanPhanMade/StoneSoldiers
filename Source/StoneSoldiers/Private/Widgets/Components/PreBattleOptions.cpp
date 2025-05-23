/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/PreBattleOptions.h"
#include "Widgets/InGameHud_Singleplayer.h"
#include "Components/Button.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"


bool UPreBattleOptions::SetParentHUD(class UUserWidget* Parent)
{
	
	if (UInGameHud_Singleplayer* ParentWidget = Cast<UInGameHud_Singleplayer>(Parent))
	{
		ParentHUD =  Cast<UInGameHud_Singleplayer>(Parent);
		return true;
	}
	return false;
}

bool UPreBattleOptions::Initialize()
{
	if (!Super::Initialize()) return false;

	
	return true;
}

void UPreBattleOptions::NativeConstruct()
{
	Super::NativeConstruct();
	if (StartFightButton) StartFightButton->OnClicked.AddDynamic(this, &ThisClass::StartFight);
	else UE_LOG(LogTemp, Display, TEXT(" StartFightButtonInvalid |  UPreBattleOptions | NativeConstruct"));
	

}

void UPreBattleOptions::StartFight()
{
	if (ParentHUD)
	{
		ParentHUD->GoToMainInGameOverlay();
	}
	else
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("Parent HUD not added. | UPreBattleOptions | StartFight");
	}
}
