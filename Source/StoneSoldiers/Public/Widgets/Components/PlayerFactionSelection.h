// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerFactionSelection.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UPlayerFactionSelection : public UUserWidget
{
	GENERATED_BODY()

public: 
 
protected: 
	virtual bool Initialize() override;
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UComboBoxString* FactionOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* RemovePlayerButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* AddPlayerButton;

	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UFUNCTION()
	void ToggleOpenSlotForPlayer();

};
