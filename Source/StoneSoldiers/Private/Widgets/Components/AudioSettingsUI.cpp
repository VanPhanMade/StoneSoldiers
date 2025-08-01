/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/AudioSettingsUI.h"
#include "Components/Slider.h"
#include "FMODBlueprintStatics.h"
#include "FMODStudioModule.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

bool UAudioSettingsUI::Initialize()
{
    if(!Super::Initialize()) return false;

    if (MasterVolumeSlider)
    {
        float SavedVolume = LoadAudioSettings();
        MasterVolumeSlider->SetValue(SavedVolume);
        SetMasterBusVolume(SavedVolume);
        
        MasterVolumeSlider->OnValueChanged.AddDynamic(this, &ThisClass::SetMasterBusVolume);
    }

    return true;
}

void UAudioSettingsUI::SetMasterBusVolume(float SliderValue)
{
    if (IFMODStudioModule* FMODStudioModule = FModuleManager::GetModulePtr<IFMODStudioModule>("FMODStudio"))
    {
        FMOD::Studio::Bus* MasterBus = nullptr;
        FMOD_RESULT Result = FMODStudioModule->GetStudioSystem(EFMODSystemContext::Runtime)->getBus("bus:/Master", &MasterBus);

        if (Result == FMOD_OK && MasterBus)
        {
            float Volume = FMath::Clamp(SliderValue, 0.0f, 1.0f); // Normalize slider value
            MasterBus->setVolume(Volume); // Set the volume

            
            
            UE_LOG(LogTemp, Warning, TEXT("Master Bus Volume: %f"), Volume);
        }
    }

    // Save the updated volume
    SaveAudioSettings(SliderValue);
    
}

void UAudioSettingsUI::SaveAudioSettings(float Volume)
{
    GConfig->SetFloat(
        TEXT("/Script/Engine.AudioSettings"),
        TEXT("MasterVolume"),
        Volume,
        GGameUserSettingsIni
    );
}

float UAudioSettingsUI::LoadAudioSettings() const
{
    float Volume = 1.0f; // Default volume

    GConfig->GetFloat(
        TEXT("/Script/Engine.AudioSettings"),
        TEXT("MasterVolume"),
        Volume,
        GGameUserSettingsIni
    );
    
    return Volume;
}