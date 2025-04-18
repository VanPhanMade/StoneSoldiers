/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/GameplayInteractionOptions.h"
#include "PlayerControllers/SS_PlayerController_Singleplayer.h"
#include "Actors/BaseUnit.h"
#include "Actors/CursorIndicator.h"
#include "Actors/TileMap.h"
#include "Actors/UnitTile.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Widgets/InGameHud_Singleplayer.h"
#include "PlayerStates/StoneSoldierPlayerState.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

void UGameplayInteractionOptions::InitUnitInformation()
{
	UE_LOG(LogTemp, Display, TEXT("Adjusting UI for selected unit"));
}

bool UGameplayInteractionOptions::SetParentHUD(class UUserWidget* Parent)
{
	if (Parent)
	{
		ParentHUD = Cast<class UInGameHud_Singleplayer>(Parent);
	}

	return ParentHUD != nullptr;
}

bool UGameplayInteractionOptions::Initialize()
{
	if (!Super::Initialize()) return false;
	if (AttackButton)
	{
		AttackButton->OnClicked.AddDynamic(this, &ThisClass::GoToAttackInteractions);
	}
	if (SpellsButton)
	{
		SpellsButton->OnClicked.AddDynamic(this, &ThisClass::GoToSpellInteractions);
	}
	if (ItemsButton)
	{
		ItemsButton->OnClicked.AddDynamic(this, &ThisClass::GoToItemInteractions);
	}
	if (GuardButton)
	{
		GuardButton->OnClicked.AddDynamic(this, &ThisClass::UnitGuard);
	}
	if (WaitButton && WaitButtonWorldInteraction)
	{
		WaitButtonWorldInteraction->OnClicked.AddDynamic(this, &ThisClass::UnitWait);
		WaitButton->OnClicked.AddDynamic(this, &ThisClass::UnitWait);
	}
	if (InteractButton)
	{
		InteractButton->OnClicked.AddDynamic(this, &ThisClass::InteractNearbyWorldObject);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &ThisClass::CancelUnitAction);
	}
	if (BackButtonFromInventory)
	{
		BackButtonFromInventory->OnClicked.AddDynamic(this, &ThisClass::ReturnToInteractionOptions);
	}
	return true;
}

void UGameplayInteractionOptions::GoToAttackInteractions()
{
	if (WidgetSwitcher)
	{
		AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>();
		if (GameState)
		{
			GameState->ActiveUnit->ValidActionTiles = GameState->TileMap->GetTargetableTiles(GameState->ActiveUnit->TileCoords, GameState->ActiveUnit->CurrentWeapon.Range, false, false);
			
			if (GameState->ActiveUnit->ValidActionTiles.Num() == 0)
			{
				StoneSoldiersHelperFunctions::LogEngineMessage("No valid tiles to attack | GoToAttackInteractions | UGameplayInteractionOptions ");
				return;
			}

			for (AUnitTile* Tile : GameState->ActiveUnit->ValidActionTiles)
			{
				Tile->OnLeftClickDelegate.Clear();
				Tile->OnLeftClickDelegate.AddDynamic(Tile, &AUnitTile::ManageCombat);
			}
		}
		
		WidgetSwitcher->SetActiveWidgetIndex(2);
		ASS_PlayerController_Singleplayer* PlayerController = Cast<ASS_PlayerController_Singleplayer>(GetOwningPlayer());
		AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
		PlayerState->GoToStateFromCurrent("Targeting Unit Action");
	}
}

void UGameplayInteractionOptions::InteractNearbyWorldObject()
{
	AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>();
	GameState->ActiveUnit->EndTurn();
}

void UGameplayInteractionOptions::GoToSpellInteractions()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(4); 
	}
}

void UGameplayInteractionOptions::GoToItemInteractions()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(4); 
	}
}

void UGameplayInteractionOptions::UnitGuard()
{
	AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>();
	GameState->ActiveUnit->EndTurn();
	
	ASS_PlayerController_Singleplayer* PlayerController = Cast<ASS_PlayerController_Singleplayer>(GetOwningPlayer());
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	PlayerState->GoToStateFromCurrent("My Turn");
}

void UGameplayInteractionOptions::UnitWait()
{
	AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>();
	GameState->ActiveUnit->EndTurn();

	ASS_PlayerController_Singleplayer* PlayerController = Cast<ASS_PlayerController_Singleplayer>(GetOwningPlayer());
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	
	PlayerState->GoToStateFromCurrent("My Turn");
}

void UGameplayInteractionOptions::CancelUnitAction()
{
	UE_LOG(LogTemp, Display, TEXT("Canceling"));
	
	AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>();
	GameState->ActiveUnit->EndTurn();

	ASS_PlayerController_Singleplayer* PlayerController = Cast<ASS_PlayerController_Singleplayer>(GetOwningPlayer());
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	
	PlayerState->GoToStateFromCurrent("My Turn");
}

void UGameplayInteractionOptions::ReturnToInteractionOptions()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0); // Should choose from 0 or one based off if we are moving a unit into range of a interactable or just enemies
	}
}
