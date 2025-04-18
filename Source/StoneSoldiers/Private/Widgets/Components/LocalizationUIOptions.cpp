/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/LocalizationUIOptions.h"
#include "Components/ComboBoxString.h"

bool ULocalizationUIOptions::Initialize()
{
    if(!Super::Initialize()) return false;

    if(LanguageOptions)
    {
        LanguageOptions->ClearOptions();
        LanguageOptions->AddOption(TEXT("English"));
        LanguageOptions->AddOption(TEXT("Chinese"));
        LanguageOptions->AddOption(TEXT("Japanese"));
        LanguageOptions->AddOption(TEXT("Korean"));
        LanguageOptions->AddOption(TEXT("Spanish"));
        LanguageOptions->AddOption(TEXT("German"));
        LanguageOptions->AddOption(TEXT("French"));
        LanguageOptions->AddOption(TEXT("Portuguese"));
        LanguageOptions->AddOption(TEXT("Russian"));
        LanguageOptions->AddOption(TEXT("Arabic"));

        LanguageOptions->OnSelectionChanged.AddDynamic(this, &ThisClass::OnComboBoxSelectionChanged);

        FString SavedCultureCode;
        if (GConfig->GetString(
                TEXT("/Script/Engine.GameUserSettings"),
                TEXT("SelectedLanguage"),
                SavedCultureCode,
                GGameUserSettingsIni))
        {
            FInternationalization::Get().SetCurrentCulture(SavedCultureCode);

            // Set the combobox selection based on the culture code
            FString SelectedLanguage;
            if (SavedCultureCode == "en")       SelectedLanguage = "English";
            else if (SavedCultureCode == "zh")  SelectedLanguage = "Chinese";
            else if (SavedCultureCode == "ja")  SelectedLanguage = "Japanese";
            else if (SavedCultureCode == "ko")  SelectedLanguage = "Korean";
            else if (SavedCultureCode == "es")  SelectedLanguage = "Spanish";
            else if (SavedCultureCode == "de")  SelectedLanguage = "German";
            else if (SavedCultureCode == "fr")  SelectedLanguage = "French";
            else if (SavedCultureCode == "pt")  SelectedLanguage = "Portuguese";
            else if (SavedCultureCode == "ru")  SelectedLanguage = "Russian";
            else if (SavedCultureCode == "ar")  SelectedLanguage = "Arabic";

            LanguageOptions->SetSelectedOption(SelectedLanguage);
        }

    }



    return true;
}


void ULocalizationUIOptions::OnComboBoxSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    // UE_LOG(LogTemp, Log, TEXT("Selected Item: %s"), *SelectedItem);
    FString CultureCode;

    if (SelectedItem == "English")       CultureCode = "en";
    else if (SelectedItem == "Chinese") CultureCode = "zh";
    else if (SelectedItem == "Japanese") CultureCode = "ja";
    else if (SelectedItem == "Korean")  CultureCode = "ko";
    else if (SelectedItem == "Spanish") CultureCode = "es";
    else if (SelectedItem == "German")  CultureCode = "de";
    else if (SelectedItem == "French")  CultureCode = "fr";
    else if (SelectedItem == "Portuguese") CultureCode = "pt";
    else if (SelectedItem == "Russian") CultureCode = "ru";
    else if (SelectedItem == "Arabic")  CultureCode = "ar";

    if (!CultureCode.IsEmpty())
    {
        FInternationalization::Get().SetCurrentCulture(CultureCode);
        SaveLanguagePreference(CultureCode); // Save the culture preference
    }
}

void ULocalizationUIOptions::SaveLanguagePreference(const FString &CultureCode)
{
    GConfig->SetString(
        TEXT("/Script/Engine.GameUserSettings"),
        TEXT("SelectedLanguage"),
        *CultureCode,
        GGameUserSettingsIni
    );
}