// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsSettingsUIOptions.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UGraphicsSettingsUIOptions : public UUserWidget
{
	GENERATED_BODY()

public: 
 
protected: 
	virtual bool Initialize() override;
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UComboBoxString* GraphicsOptions;
	
	UFUNCTION()
    void OnComboBoxSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	void ApplyGraphicsSettings(const FString& QualityLevel);
    void SaveGraphicsSettings(const FString& QualityLevel);
    FString LoadGraphicsSettings();
	
};
