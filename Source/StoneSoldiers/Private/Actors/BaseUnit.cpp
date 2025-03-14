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


// Sets default values
ABaseUnit::ABaseUnit()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Establishes the Components
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
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
	Model->SetStaticMesh(UnitData.ModelAsset);

	OwningPlayer = Player;

	// Creates the Abilities
	for (int i = 0; i < UnitData.UnitCoreData.Abilities.Num(); i++)
	{
		UBaseAbilityComponent* Component = Cast<UBaseAbilityComponent>(AddComponentByClass(UnitData.UnitCoreData.Abilities[i], true, FTransform(), true));
		FinishAddComponent(Component, true, FTransform());
		Component->Init(this);
		Abilities.Add(Component);
	}

	// Creates Actions
	for (int i = 0; i < UnitData.UnitCoreData.Actions.Num(); i++)
	{
		UBaseActionComponent* Component = Cast<UBaseActionComponent>(AddComponentByClass(UnitData.UnitCoreData.Actions[i], true, FTransform(), true));
		FinishAddComponent(Component, true, FTransform());
		Component->Init(this);
		Actions.Add(Component);
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
	int Damage = CurrentStrength + CurrentWeapon.Damage - CurrentDefenses[CurrentWeapon.DamageType];
	Target->CurrentHealth -= Damage;
	// StoneSoldiersHelperFunctions::LogEngineMessage(FString("Target Health Remaining: ") + FString::FromInt(Target->CurrentHealth));
}
