// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnitSelectionSinglePlayerPC.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AUnitSelectionSinglePlayerPC : public APlayerController
{
	GENERATED_BODY()

public: 
 
protected: 
	virtual void BeginPlay() override;
 
private:
	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UUnitSelectionSingleplayerUI> UnitSelectionWidget;

	class UUnitSelectionSingleplayerUI* UnitSelectionRef;
	
};
