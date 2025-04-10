// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "TileVisuals.generated.h"

USTRUCT(BlueprintType)
struct FTileVisualsStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TileScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMesh> BaseStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UMaterialInstance> BaseStaticMeshMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMesh> OverlayMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UMaterialInstance> OnHoverMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UMaterialInstance> OnSelectionMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UMaterialInstance> OverlayBaseMaterial;

    FTileVisualsStruct()
        : TileScale(FVector(1.0f, 1.0f, 1.0f))
        , BaseStaticMesh(nullptr)
        , BaseStaticMeshMaterial(nullptr)
        , OverlayMesh(nullptr)
        , OnHoverMaterial(nullptr)
        , OnSelectionMaterial(nullptr)
        , OverlayBaseMaterial(nullptr) {}
};

USTRUCT(BlueprintType)
struct FTileData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FTileVisualsStruct TileVisuals;
};
/**
 * 
 */
class STONESOLDIERS_API TileVisuals
{
public:
	TileVisuals();
	~TileVisuals();
};
