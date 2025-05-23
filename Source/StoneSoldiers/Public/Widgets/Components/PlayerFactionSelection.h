// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	bool bSinglePlayerSlot = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	bool bSinglePlayer = false;

	bool bActivePlayer = false;

	UFUNCTION()
	void ToggleOpenSlotForPlayer();

public:
	FORCEINLINE bool IsActivelyUsed() const { return bSinglePlayerSlot ? true : bActivePlayer; }
	FORCEINLINE FString GetCurrentFaction() const { return FactionOptions != nullptr ? FactionOptions->GetSelectedOption() : TEXT("FactionNone"); }
};
