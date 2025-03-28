// ©Van Phan


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


// Sets default values
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

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	State = EUnitState::Ready;
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// Initializes Unit
/// </summary>
/// <param name="Data">The Unit Data to pass along to the unit. </param>
/// <param name="Player">Unique ID of player that owns initialized unit. </param>
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

	//FVector TestVec = TileCoords;
	//UBaseActionComponent* ActionComp = nullptr;
	//AIComponent->RunUnit();

	//StoneSoldiersHelperFunctions::LogEngineMessage(FString::FromInt(TestVec.X));
	// End Temp AI Behavior

	State = EUnitState::Finished;

	// Defines Variable Stats as Needed
	CurrentHealth = Data.UnitCoreData.Health;
	CurrentStrength = Data.UnitCoreData.Strength;

	CurrentDefenses.Add(TEnumAsByte<EDamageTypes>(Crushing), Data.UnitCoreData.CrushingDefense);
	CurrentDefenses.Add(TEnumAsByte<EDamageTypes>(Slashing), Data.UnitCoreData.SlashingDefense);
	CurrentDefenses.Add(TEnumAsByte<EDamageTypes>(Piercing), Data.UnitCoreData.PiercingDefense);
	CurrentDefenses.Add(TEnumAsByte<EDamageTypes>(Magic), Data.UnitCoreData.MagicalDefense);
}

/// <summary>
/// Process the unit's turn, going from movement into action
/// </summary>
void ABaseUnit::ProcessTurn()
{
	// Temp Combat Action
	if (AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>())
	{
		ValidActionTiles = GameState->TileMap->GetTargetableTiles(TileCoords, CurrentWeapon.Range, false, false);
	}
	else
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("Game state invalid | Process Turn Func | Base Unit ");
	}

	// Updates Affected Tiles OnLeftClickDelegate
	if (ValidActionTiles.Num() == 0)
	{
		EndTurn();
		return;
	}

	for (AUnitTile* Tile : ValidActionTiles)
	{
		Tile->OnLeftClickDelegate.BindUObject(Tile, &AUnitTile::ManageCombat);
	}
}

/// <summary>
/// Ends the Turn
/// Is resoponsible for finalizing the unit's state and reseting necessary data on tiles impacted by its action
/// </summary>
void ABaseUnit::EndTurn()
{
	// Resets Affected Tile Delegates
	for (AUnitTile* Tile : ValidActionTiles)
	{
		Tile->OnLeftClickDelegate.BindUObject(Tile, &AUnitTile::ManageBaseLeftClick);
		Tile->UnhighlightTile();
	}

	// Sets the Unit's End State and Broadcasts the turn has finished
	ValidActionTiles.Empty();
	State = EUnitState::Finished;
	OnTurnFinishedDelegate.Broadcast(this);
}

void ABaseUnit::Attack(ABaseUnit* Target)
{
	// DEPRECATED : Logic has been abstracted to combat action component, which is an actor component
	int Damage = CurrentStrength + CurrentWeapon.Damage - CurrentDefenses[CurrentWeapon.DamageType];
	Target->CurrentHealth -= Damage;
	
}

void ABaseUnit::ResolveDamage(int damage)
{
	CurrentHealth -= damage;
	StoneSoldiersHelperFunctions::LogEngineMessage("Damage Taken! | ABaseUnit | ResolveDamage");
	if (CurrentHealth <= 0)
	{
		if (AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>())
		{
			ASS_PlayerPawn_Singleplayer* OwnerPawn = Cast<ASS_PlayerPawn_Singleplayer>(GameState->PlayersInGame[OwningPlayer]);
			if (OwnerPawn == nullptr)
			{
				StoneSoldiersHelperFunctions::LogEngineMessage("Failed to cast player to a player type! | ABaseUnit | ResolveDamage");
				return;
			}
			
			if (GameState->PlayerUnits.Contains(OwningPlayer))
			{
				GameState->PlayerUnits[OwningPlayer].Remove(this);
				if (GameState->PlayerUnits[OwningPlayer].Num() == 0)
				{
					GameState->PlayerUnits.Remove(OwningPlayer);
				}
			}
			
			ETeamID TeamID = OwnerPawn->TeamID; 
			if (GameState->TeamUnits.Contains(TeamID))
			{
				GameState->TeamUnits[TeamID].Remove(this);

				// Remove entry if empty
				if (GameState->TeamUnits[TeamID].Num() == 0)
				{
					GameState->TeamUnits.Remove(TeamID);
				}
			}

			Destroy();
		}
		else
		{
			StoneSoldiersHelperFunctions::LogEngineMessage("Can't get GameMode for removing unit! | ABaseUnit | ResolveDamage");
		}
	}
}
