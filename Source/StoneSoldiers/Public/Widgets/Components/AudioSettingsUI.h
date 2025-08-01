// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AudioSettingsUI.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UAudioSettingsUI : public UUserWidget
{
	GENERATED_BODY()

public: 
 
protected: 
	virtual bool Initialize() override;
 
private:
	UPROPERTY(meta = (BindWidget))
    class USlider* MasterVolumeSlider;

	UFUNCTION()
    void SetMasterBusVolume(float SliderValue);

	void SaveAudioSettings(float Volume);
    float LoadAudioSettings() const;
	
};
