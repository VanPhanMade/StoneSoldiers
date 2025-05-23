/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "ActorComponents/FlyingAbility.h"
#include "Actors/BaseUnit.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

UFlyingAbility::UFlyingAbility()
{
	AbilityName = FString("Flying");
	AbilityTiming = EAbilityTiming::Passive;
}

void UFlyingAbility::Init(ABaseUnit* Unit)
{
	Super::Init(Unit);

	UseAbility();
}

void UFlyingAbility::UseAbility()
{
	CreateFilter();

	OwningUnit->MovementFilter = FlyingFilter;
}

void UFlyingAbility::CreateFilter()
{
	FlyingFilter.Add(ETerrainType::Forest, 1);
}
