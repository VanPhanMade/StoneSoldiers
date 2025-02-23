// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionDataUI.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API USessionDataUI : public UUserWidget
{
	GENERATED_BODY()

public: 
	UPROPERTY(BlueprintReadWrite)
	class UMultiplayerSessionsUI* ParentWidget; // Assigned in blueprints

	UFUNCTION()
	void HighlightSessionInfoWidget(bool bHighlight);
 
protected: 
	virtual bool Initialize() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

 
private:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UTextBlock* GameName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UTextBlock* MaxFunds;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UTextBlock* CurrentNumberOfPlayers;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UTextBlock* MaxNumberOfPlayers;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UTextBlock* MatchType;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UTextBlock* HostName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UOverlay* HighlightBorder;
	
};
