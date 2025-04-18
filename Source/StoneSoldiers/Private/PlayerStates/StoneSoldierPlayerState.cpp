/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "PlayerStates/StoneSoldierPlayerState.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

FPlayerInGameStates* AStoneSoldierPlayerState::GoToStateFromCurrent(FString NewState)
{
	if (FPlayerInGameStates** FoundState = CurrentState->ChildrenStates.Find(NewState))
	{
		StateStack.Push(*FoundState);
		CurrentState = *FoundState;
		
		// StoneSoldiersHelperFunctions::LogEngineMessage(FString::Printf(TEXT("Current State: %s | StoneSoldiersPlayerState | GoToStateFromCurrentState"), *CurrentState->StateName));
		OnPlayerStateChange.Broadcast(CurrentState->StateName);
		return *FoundState;
	}
	return CurrentState;
}

FPlayerInGameStates* AStoneSoldierPlayerState::PopAndGoBackAState()
{
	if (StateStack.Num() > 1) // because we don't want to pop PreBattle off the stack
	{
		StateStack.Pop();
		CurrentState = StateStack.Top();
		OnPlayerStateChange.Broadcast(CurrentState->StateName);
		return CurrentState;
	}
	
	return nullptr;
}

FPlayerInGameStates* AStoneSoldierPlayerState::UpdateStateForNewTurn(bool bIsThisPlayerTurn)
{
	OnPlayerStateChange.Broadcast(CurrentState->StateName);
	return CurrentState;
}

void AStoneSoldierPlayerState::BeginPlay()
{
	Super::BeginPlay();
	// Initialize all states
	FPlayerInGameStates* BeforeCombat = new FPlayerInGameStates();
	BeforeCombat->StateName = "Before Combat"; // Placing units, checking inventory, readying for battle

	FPlayerInGameStates* MyTurn = new FPlayerInGameStates();
	MyTurn->StateName = "My Turn"; // Player is able to move around on map, select units

	FPlayerInGameStates* MovingUnit = new FPlayerInGameStates();
	MovingUnit->StateName = "Moving Unit"; // Unit is selected, player is decided a tile to move to

	FPlayerInGameStates* ChoosingUnitAction = new FPlayerInGameStates();
	ChoosingUnitAction->StateName = "Choosing Unit Action"; // Choose to Attack, Interact, Open Inventory, Guard, or Wait

	FPlayerInGameStates* TargetingUnitAction = new FPlayerInGameStates();
	TargetingUnitAction->StateName = "Targeting Unit Action"; // Aiming the action selected, if it needs to be aimed
	
	FPlayerInGameStates* EndingTurn = new FPlayerInGameStates(); 
	EndingTurn->StateName = "Ending Turn"; // After all units have attacked, moved, etc. add data replicates
	
	FPlayerInGameStates* NotMyTurn = new FPlayerInGameStates();
	NotMyTurn->StateName = "Not My Turn"; // Can still look around map, but nothing gets replicated until next ending turn phase

	FPlayerInGameStates* LookingAtMainMenu = new FPlayerInGameStates();
	LookingAtMainMenu->StateName = "Looking At Main Menu"; // Looking to main to change audio, keys,etc. ( not game impacting settings )

	FPlayerInGameStates* InspectingUnit = new FPlayerInGameStates();
	InspectingUnit->StateName = "Inspecting Unit"; // Allows us to look at units while we are waiting for our turn

	// Connecting states
	BeforeCombat->ChildrenStates.Add("My Turn", MyTurn);
	BeforeCombat->ChildrenStates.Add("Not My Turn", NotMyTurn);
	BeforeCombat->ChildrenStates.Add("Looking At Main Menu", LookingAtMainMenu);

	MyTurn->ChildrenStates.Add("Inspecting Unit", InspectingUnit);
	MyTurn->ChildrenStates.Add("Moving Unit", MovingUnit);
	MyTurn->ChildrenStates.Add("Looking At Main Menu", LookingAtMainMenu);

	MovingUnit->ChildrenStates.Add("Choosing Unit Action", ChoosingUnitAction);
	MovingUnit->ChildrenStates.Add("Looking At Main Menu", LookingAtMainMenu);

	ChoosingUnitAction->ChildrenStates.Add("Ending Turn", EndingTurn);
	ChoosingUnitAction->ChildrenStates.Add("Looking At Main Menu", LookingAtMainMenu);
	ChoosingUnitAction->ChildrenStates.Add("My Turn", MyTurn);
	ChoosingUnitAction->ChildrenStates.Add("Targeting Unit Action", TargetingUnitAction);

	TargetingUnitAction->ChildrenStates.Add("Ending Turn", EndingTurn);
	TargetingUnitAction->ChildrenStates.Add("My Turn", MyTurn);

	EndingTurn->ChildrenStates.Add("Not My Turn", NotMyTurn);
	EndingTurn->ChildrenStates.Add("My Turn", MyTurn);

	NotMyTurn->ChildrenStates.Add("Inspecting Unit", InspectingUnit);
	NotMyTurn->ChildrenStates.Add("Looking At Main Menu", LookingAtMainMenu);
	NotMyTurn->ChildrenStates.Add("Ending Turn", EndingTurn);

	InspectingUnit->ChildrenStates.Add("LookingAtMainMenu", LookingAtMainMenu);

	// Add all states to an iterative list for debugging
	AllStates.Add(BeforeCombat);
	AllStates.Add(MyTurn);
	AllStates.Add(MovingUnit);
	AllStates.Add(ChoosingUnitAction);
	AllStates.Add(TargetingUnitAction);
	AllStates.Add(NotMyTurn);
	AllStates.Add(LookingAtMainMenu);
	AllStates.Add(InspectingUnit);

	// All players start in before combat
	CurrentState = BeforeCombat;
	StateStack.Push(BeforeCombat);
}
