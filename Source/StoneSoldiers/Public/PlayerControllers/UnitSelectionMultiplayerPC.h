// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnitSelectionMultiplayerPC.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AUnitSelectionMultiplayerPC : public APlayerController
{
	GENERATED_BODY()
	
public: 
 
protected: 
	virtual void BeginPlay() override;
 
private:
	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UUnitSelectionMultiplayerUI> UnitSelectionWidget;

	class UUnitSelectionMultiplayerUI* UnitSelectionRef;

};
