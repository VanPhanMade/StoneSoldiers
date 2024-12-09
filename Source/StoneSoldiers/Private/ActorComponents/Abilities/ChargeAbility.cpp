// ©Van Phan


#include "GameStates/StoneSoldiersGameState.h"
#include "Actors/TileMap.h"
#include "ActorComponents/Abilities/ChargeAbility.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

void UChargeAbility::Init(ABaseUnit* Unit)
{
	Super::Init(Unit);

	Unit->OnBeginMovement.AddDynamic(this, &UChargeAbility::FindAdjacentUnits);

	UWorld* World = GetWorld();
	GameState = World->GetGameState<AStoneSoldiersGameState>();
}

void UChargeAbility::FindAdjacentUnits()
{
	AdjacentUnits.Empty();
	AdjacentUnits = GameState->TileMap->GetNeighboringUnits(OwningUnit->GetTileCoords());
	StoneSoldiersHelperFunctions::LogEngineMessage(FString("Num Adjacent Units: ") + FString::FromInt(AdjacentUnits.Num()));
}

void UChargeAbility::CheckWasTargetAdjacent()
{

}
