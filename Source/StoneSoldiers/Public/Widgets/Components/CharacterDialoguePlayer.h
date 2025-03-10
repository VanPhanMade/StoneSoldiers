// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterDialoguePlayer.generated.h"

USTRUCT()
struct FSinglePanelData
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FCharacterDialogue
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere)
	TArray<FSinglePanelData> DialoguePanels;
};

UENUM(BlueprintType)
enum class EDialogueRow : uint8
{
	TopRow,
	MiddleRow,
	BottomRow,
};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartDialogue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextPanelDialogue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishDialogue);

UCLASS()
class STONESOLDIERS_API UCharacterDialoguePlayer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnStartDialogue OnStartDialogue;
	FOnNextPanelDialogue OnNextPanelDialogue;
	FOnFinishDialogue OnFinishDialogue;

	virtual void NextPanel() const; // Updates background, plays text, plays sounds
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FCharacterDialogue CharacterDialogue; //Represents one entire dialogue cutscene

private:
	void SetDialogueRowVisibility(EDialogueRow Row, bool bIsShown) const;
	void AdjustFocusOnRow(EDialogueRow Row, bool bFullFocused) const; // Focused Row will unfocus the rest of the rows
	void PlayDialogueRow(EDialogueRow Row) const;
};
