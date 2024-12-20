// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitSelectionCampaignUI.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UUnitSelectionCampaignUI : public UUserWidget
{
	GENERATED_BODY()
	
public: 
 
protected: 
	virtual bool Initialize() override;
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* GoToCampaignLevelButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UUniformGridPanel* StoneCasterGroup1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UUniformGridPanel* StoneCasterGroup2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UUniformGridPanel* StoneCasterGroup3;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UUniformGridPanel* StoneCasterGroup4;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UUniformGridPanel* AuxilleryUnitsGroup;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UUniformGridPanel* CasterOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UUniformGridPanel* GolemOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UUniformGridPanel* AuxilleryUnitsOptions;

	UFUNCTION()
	void TravelToCampaignLevel();



};
