// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattlesOptions.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UBattlesOptions : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UMainMenu* MainMenuWidget; // Data saved in main menu class

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* CustomBattlesButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* MultiplayerBattlesButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* LeaderboardsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* ReplaysButton;

	UFUNCTION()
	void OpenCustomBattles();

	UFUNCTION()
	void OpenMultiplayerBattles();

	UFUNCTION()
	void OpenLeaderboard();

	UFUNCTION()
	void OpenReplays();

};
