// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Structs/UnitData.h"
#include "UnitDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UUnitDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
    // Data specific to the unit
    UPROPERTY()
    int32 UnitID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUIDataStruct IncomingUIData;

	UPROPERTY(BlueprintReadOnly)
	FName IncomingRowOption;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EUnitType> IncomingType;


	
};
