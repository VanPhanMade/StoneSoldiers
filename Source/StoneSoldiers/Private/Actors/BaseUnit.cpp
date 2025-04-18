/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Actors/BaseUnit.h"
#include "ActorComponents/BaseAbilityComponent.h"
#include "ActorComponents/BaseActionComponent.h"
#include "ActorComponents/BaseUnitAIComponent.h"
#include "ActorComponents/AIComponents/TestAIComponent.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Actors/TileMap.h"
#include "Actors/UnitTile.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Pawns/SS_PlayerPawn_Singleplayer.h"
#include "AnimInstances/BaseUnitAnimInstance.h"
#include "Materials/MaterialExpressionSceneColor.h"


/// Sets default values for this unit.
ABaseUnit::ABaseUnit()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Establishes the Components
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	Model = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(RootComponent);
	Model->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// TEMP Weapon Declaration
	CurrentWeapon.Damage = 6;
	CurrentWeapon.Range = 4;
	CurrentWeapon.DamageType = TEnumAsByte<EDamageTypes>(Magic);
}

void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	State = EUnitState::Ready;
}

void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// Initializes the unit with data and assigns it to a player.
/// @param Data The unit data to initialize the unit with.
/// @param Player Unique ID of the player who owns the initialized unit.
void ABaseUnit::Init(const FUnitData& Data, const EPlayerID Player)
{
	// Stores the Data
	UnitData = Data;
	Model->SetSkeletalMesh(UnitData.ModelAsset);
	if (UnitData.AnimClass !=nullptr)
	{
		Model->SetAnimInstanceClass(UnitData.AnimClass);
	}

	OwningPlayer = Player;

	// Creates the Abilities
	for (int i = 0; i < UnitData.UnitCoreData.Abilities.Num(); i++)
	{
		UBaseAbilityComponent* Component = Cast<UBaseAbilityComponent>(AddComponentByClass(UnitData.UnitCoreData.Abilities[i], true, FTransform(), true));
		if (Component)
		{
			FinishAddComponent(Component, true, FTransform());
			Component->Init(this);
			Abilities.Add(Component);
		}
		else
		{
			StoneSoldiersHelperFunctions::LogEngineMessage("Unit Missing Ability! | ABaseUnit | Init");
		}
	}

	// Creates Actions
	for (int i = 0; i < UnitData.UnitCoreData.Actions.Num(); i++)
	{
		UBaseActionComponent* Component = Cast<UBaseActionComponent>(AddComponentByClass(UnitData.UnitCoreData.Actions[i], true, FTransform(), true));
		if (Component)
		{
			FinishAddComponent(Component, true, FTransform());
			Component->Init(this);
			Actions.Add(Component);
		}
		else
		{
			StoneSoldiersHelperFunctions::LogEngineMessage("Unit Missing Action! | ABaseUnit | Init");
		}
	}
	
	// TEMP CREATION OF AN AI BEHAVIOR
	AIComponent = Cast<UBaseUnitAIComponent>(AddComponentByClass(UTestAIComponent::StaticClass(), true, FTransform(), true));
	FinishAddComponent(AIComponent, true, FTransform());
	AIComponent->Init(this);

	State = EUnitState::Finished;

	// Defines Variable Stats as Needed
	CurrentHealth = Data.UnitCoreData.Health;
	CurrentStrength = Data.UnitCoreData.Strength;

	CurrentDefenses.Add(TEnumAsByte<EDamageTypes>(Crushing), Data.UnitCoreData.CrushingDefense);
	CurrentDefenses.Add(TEnumAsByte<EDamageTypes>(Slashing), Data.UnitCoreData.SlashingDefense);
	CurrentDefenses.Add(TEnumAsByte<EDamageTypes>(Piercing), Data.UnitCoreData.PiercingDefense);
	CurrentDefenses.Add(TEnumAsByte<EDamageTypes>(Magic), Data.UnitCoreData.MagicalDefense);
}

/// Ends the turn, finalizing the unit's state and resetting data on affected tiles.
/// Clears the tiles impacted by the unit's actions.
void ABaseUnit::EndTurn()
{
	// Resets Tiles
	for (AUnitTile* Tile : ValidActionTiles)
	{
		Tile->OnLeftClickDelegate.Clear();
		Tile->OnLeftClickDelegate.AddDynamic(Tile, &AUnitTile::ManageBaseLeftClick);
		Tile->UnhighlightTile();
	}

	ValidActionTiles.Empty();
	State = EUnitState::Finished;
	OnTurnFinishedDelegate.Broadcast(this);

	AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>();
	GameState->ActiveUnit = nullptr;
}

/// Attacks a target unit.
/// @param Target The unit that will be attacked.
void ABaseUnit::Attack(ABaseUnit* Target)
{
	// DEPRECATED : Logic has been abstracted to combat action component, which is an actor component
	int Damage = CurrentStrength + CurrentWeapon.Damage - CurrentDefenses[CurrentWeapon.DamageType];
	Target->CurrentHealth -= Damage;
}

/// Resolves the damage taken by this unit.
/// When a unit dies, clear references to all arrays that make reference unit and tiles
/// @param damage The amount of damage to apply to the unit's health.
void ABaseUnit::ResolveDamage(int damage)
{
	CurrentHealth -= damage;
	if (CurrentHealth <= 0)
	{
		OnUnitDeathDelegate.Broadcast(this);
		Destroy();
	}
}
