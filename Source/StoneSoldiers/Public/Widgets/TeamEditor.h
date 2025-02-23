// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamEditor.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UTeamEditor : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	class UButton* BackToMainButton;

protected:
	virtual bool Initialize() override;

private:
	void LoadSelectionData();
	void SaveCurrentSelection();

	// Left hand side
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UHorizontalBox* ArcheryRow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UHorizontalBox* FootmenRow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UHorizontalBox* CavalryRow;

	// Right hand side
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UHorizontalBox* CurrentSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UTextBlock* UnitInformation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* SaveSelection;

	

	
};
