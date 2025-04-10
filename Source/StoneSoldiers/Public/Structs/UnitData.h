// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UnitData.generated.h"

UENUM()
enum EUnitType : uint8
{
	StoneCaster,
	Golem,
	Auxiliary
};

UENUM()
enum EGolemStability : uint8
{
	Independant,
	Stable,
	Unstable
};


USTRUCT(BlueprintType)
struct FUnitCoreDataStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 PointsCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Prowess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Dexterity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Luck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Resolve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 PiercingDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 SlashingDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 CrushingDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MagicalDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UBaseAbilityComponent>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UBaseActionComponent>> Actions;

	FUnitCoreDataStruct() : PointsCost(0),
	                        Health(0),
							Movement(0),
							Strength(0),
							Prowess(0),
							Dexterity(0),
							Luck(0),
							Resolve(0),
	                        PiercingDefense(0),
	                        SlashingDefense(0),
	                        CrushingDefense(0),
	                        MagicalDefense(0)
	{
	}
};

USTRUCT(BlueprintType)
struct FStoneCasterDataStruct
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 InfluenceRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ControlRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> AllowedGolems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UBaseAbilityComponent>> ConferredAbilities;

	FStoneCasterDataStruct() : 
		InfluenceRange(0),
		ControlRange(0),
		AllowedGolems(TArray<FText>()),
		ConferredAbilities(TArray<TSubclassOf<class UBaseAbilityComponent>>()) {}
};

USTRUCT(BlueprintType)
struct FGolemDataStruct
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGolemStability> Stability;

	FGolemDataStruct() :
		Stability(TEnumAsByte<EGolemStability>(Independant)) {}
};

USTRUCT(BlueprintType)
struct FUIDataStruct
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText FlavorText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* PanelImage;

	FUIDataStruct() :
		PanelImage(nullptr) {}
};


USTRUCT(BlueprintType)
struct FUnitData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EUnitType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* ModelAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UBaseUnitAnimInstance> AnimClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUnitCoreDataStruct UnitCoreData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStoneCasterDataStruct StoneCasterData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGolemDataStruct GolemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUIDataStruct UIData;
};

/**
 * 
 */
class STONESOLDIERS_API UnitData
{
public:
	UnitData();
	~UnitData();
};
