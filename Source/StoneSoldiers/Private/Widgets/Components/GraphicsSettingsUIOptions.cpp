/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/GraphicsSettingsUIOptions.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

bool UGraphicsSettingsUIOptions::Initialize()
{
    if(!Super::Initialize()) return false;

    if(GraphicsOptions)
    {
        GraphicsOptions->ClearOptions();
        GraphicsOptions->AddOption(TEXT("Low"));
        GraphicsOptions->AddOption(TEXT("Medium"));
        GraphicsOptions->AddOption(TEXT("High"));
        GraphicsOptions->AddOption(TEXT("Epic"));
        GraphicsOptions->AddOption(TEXT("Cinematic"));
        GraphicsOptions->AddOption(TEXT("Auto"));

        GraphicsOptions->OnSelectionChanged.AddDynamic(this, &UGraphicsSettingsUIOptions::OnComboBoxSelectionChanged);

        FString SavedQualityLevel = LoadGraphicsSettings();
        if (!SavedQualityLevel.IsEmpty())
        {
            GraphicsOptions->SetSelectedOption(SavedQualityLevel);
            ApplyGraphicsSettings(SavedQualityLevel);
        }
    }

    return true;
}

void UGraphicsSettingsUIOptions::OnComboBoxSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    ApplyGraphicsSettings(SelectedItem);
    SaveGraphicsSettings(SelectedItem);
}

void UGraphicsSettingsUIOptions::ApplyGraphicsSettings(const FString& QualityLevel)
{
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    if (!UserSettings) return;

    int32 GraphicsLevel = 0;

    if (QualityLevel == "Low") GraphicsLevel = 0;
    else if (QualityLevel == "Medium") GraphicsLevel = 1;
    else if (QualityLevel == "High") GraphicsLevel = 2;
    else if (QualityLevel == "Epic") GraphicsLevel = 3;
    else if (QualityLevel == "Cinematic") GraphicsLevel = 4;
    else if (QualityLevel == "Auto") GraphicsLevel = -1; // Use platform-determined settings

    if (GraphicsLevel >= 0)
    {
        UserSettings->SetOverallScalabilityLevel(GraphicsLevel);
    }
    else
    {
        UserSettings->SetToDefaults();
    }

    UserSettings->ApplySettings(false); // Apply without restarting the engine
}

void UGraphicsSettingsUIOptions::SaveGraphicsSettings(const FString& QualityLevel)
{
    GConfig->SetString(
        TEXT("/Script/Engine.GameUserSettings"),
        TEXT("GraphicsQuality"),
        *QualityLevel,
        GGameUserSettingsIni
    );
}

FString UGraphicsSettingsUIOptions::LoadGraphicsSettings()
{
    FString QualityLevel;
    GConfig->GetString(
        TEXT("/Script/Engine.GameUserSettings"),
        TEXT("GraphicsQuality"),
        QualityLevel,
        GGameUserSettingsIni
    );

    return QualityLevel;
}


