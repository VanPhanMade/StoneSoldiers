// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LocalizationUIOptions.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API ULocalizationUIOptions : public UUserWidget
{
	GENERATED_BODY()

protected: 
	virtual bool Initialize() override;
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UComboBoxString* LanguageOptions;
	
	UFUNCTION()
    void OnComboBoxSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	void SaveLanguagePreference(const FString& CultureCode);
};
