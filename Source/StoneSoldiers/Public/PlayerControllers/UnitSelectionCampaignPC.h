// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnitSelectionCampaignPC.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AUnitSelectionCampaignPC : public APlayerController
{
	GENERATED_BODY()

public: 
 
protected: 
	virtual void BeginPlay() override;
 
private:
	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UUnitSelectionCampaignUI> UnitSelectionWidget;

	class UUnitSelectionCampaignUI* UnitSelectionRef;
	
};
