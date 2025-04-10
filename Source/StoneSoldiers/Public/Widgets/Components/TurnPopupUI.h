// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurnPopupUI.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UTurnPopupUI : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	virtual bool Initialize() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	FText MessageToDisplay;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UTextBlock* TextElement;
	
};
