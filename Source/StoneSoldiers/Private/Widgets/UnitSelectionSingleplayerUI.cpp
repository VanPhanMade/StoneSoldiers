/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/UnitSelectionSingleplayerUI.h"
#include "Components/Button.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Components/WidgetSwitcher.h"
#include "Widgets/Components/PlayerFactionSelection.h"

bool UUnitSelectionSingleplayerUI::Initialize()
{
    if(!Super::Initialize()) return false;
    if(GoToSinglePlayerLevelButton)
    {
        if(GetWorld()->GetAuthGameMode())
        {
            if(GoToSinglePlayerLevelButton) GoToSinglePlayerLevelButton->OnClicked.AddDynamic(this, &ThisClass::TravelToSingleplayerLevel);
            if(ShowMapButton) ShowMapButton->OnClicked.AddDynamic(this, &ThisClass::ShowMapDataCallback);
            if(ShowSettingsButton) ShowSettingsButton->OnClicked.AddDynamic(this, &ThisClass::ShowSessionOptionsCallback);
            if(ShowUnitInfoButton) ShowUnitInfoButton->OnClicked.AddDynamic(this, &ThisClass::ShowUnitInfoCallback);
            if(BackToMainMenuButton) BackToMainMenuButton->OnClicked.AddDynamic(this, &ThisClass::BackToMainMenuCallback);
        }
        else
        {
            GoToSinglePlayerLevelButton->SetVisibility(ESlateVisibility::Collapsed);
        }
        PlayerSlots.Empty();
        if (Slot1)PlayerSlots.AddUnique(Slot1);
        if (Slot2)PlayerSlots.AddUnique(Slot2);
        if (Slot3)PlayerSlots.AddUnique(Slot3);
        if (Slot4)PlayerSlots.AddUnique(Slot4);
        if (Slot5)PlayerSlots.AddUnique(Slot5);
        if (Slot6)PlayerSlots.AddUnique(Slot6);
        if (Slot7)PlayerSlots.AddUnique(Slot7);
        if (Slot8)PlayerSlots.AddUnique(Slot8);
    }

    return true;
}


void UUnitSelectionSingleplayerUI::TravelToSingleplayerLevel()
{
    if(WriteSelectionsToJson() && GetWorld() && GetWorld()->GetAuthGameMode())
    {
        const FString MapName = "/Game/Levels/GameLevels/GameLevelSinglePlayer";
        GetWorld()->ServerTravel(MapName, true);
    }
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage(" Server travel failed. ");
    }

}

void UUnitSelectionSingleplayerUI::ShowMapDataCallback()
{
    if(WidgetSwitcher)
    {
        WidgetSwitcher->SetActiveWidgetIndex(0);
    }
}

void UUnitSelectionSingleplayerUI::ShowSessionOptionsCallback()
{
    if(WidgetSwitcher)
    {
        WidgetSwitcher->SetActiveWidgetIndex(1);
    }
}

void UUnitSelectionSingleplayerUI::ShowUnitInfoCallback()
{
    if(WidgetSwitcher)
    {
        WidgetSwitcher->SetActiveWidgetIndex(2);
    }
}

void UUnitSelectionSingleplayerUI::BackToMainMenuCallback()
{
    if(GetWorld() && GetWorld()->GetAuthGameMode())
    {
        const FString MapName = "/Game/Levels/MainMenu/MainMenu";
        GetWorld()->ServerTravel(MapName, true);
    }
}

bool UUnitSelectionSingleplayerUI::WriteSelectionsToJson() const
{
    TSharedPtr<FJsonObject> SingleplayerMatchData = MakeShareable(new FJsonObject);

    // Map Rules 
    TSharedPtr<FJsonObject> MapRules = MakeShareable(new FJsonObject);
    MapRules->SetStringField("LevelName", "RiverMap");
    MapRules->SetStringField("GameMode", "Conquest");  // Example game mode
    MapRules->SetNumberField("Difficulty", 3);
    MapRules->SetBoolField("IsNightMode", false);
    SingleplayerMatchData->SetObjectField("MapRules", MapRules);

    // Match Settings 
    TSharedPtr<FJsonObject> MatchSettings = MakeShareable(new FJsonObject);
    MatchSettings->SetNumberField("MaxPlayers", 8);
    MatchSettings->SetBoolField("AllowRespawns", false);
    SingleplayerMatchData->SetObjectField("MatchSettings", MatchSettings);

    // Array of Players
    TArray<TSharedPtr<FJsonValue>> PlayersArray;
    
    for (int i = 0; i < PlayerSlots.Num() - 1; i++) {
        if(PlayerSlots[i] != nullptr && !PlayerSlots[i]->IsActivelyUsed()) continue; // Skips not used slots
        
        TSharedPtr<FJsonObject> PlayerData = MakeShareable(new FJsonObject);
        PlayerData->SetNumberField("ID", i + 1);  // Assign unique ID
        PlayerData->SetStringField("Faction",PlayerSlots[i]->GetCurrentFaction());

        // Stone Casters
        TArray<TSharedPtr<FJsonValue>> StoneCastersArray;
        for (int j = 1; j <= 2; j++) { // Example of 2 stone casters per player
            TSharedPtr<FJsonObject> StoneCaster = MakeShareable(new FJsonObject);
            StoneCaster->SetStringField("Name", FString::Printf(TEXT("StoneCaster%d"), j));

            // Assign up to 4 Golems
            TArray<TSharedPtr<FJsonValue>> GolemsArray;
            for (int k = 1; k <= FMath::RandRange(1, 4); k++) { // Random number of golems (1-4)
                GolemsArray.Add(MakeShareable(new FJsonValueString(FString::Printf(TEXT("Golem%d"), k))));
            }
            StoneCaster->SetArrayField("Golems", GolemsArray);
            StoneCastersArray.Add(MakeShareable(new FJsonValueObject(StoneCaster)));
        }
        PlayerData->SetArrayField("StoneCasters", StoneCastersArray);

        // Auxiliary Units
        TArray<TSharedPtr<FJsonValue>> AuxiliaryUnitsArray;
        for (int j = 1; j <= FMath::RandRange(0, 3); j++) { // Random number of auxiliary units (0-3)
            AuxiliaryUnitsArray.Add(MakeShareable(new FJsonValueString(FString::Printf(TEXT("AuxUnit%d"), j))));
        }
        PlayerData->SetArrayField("AuxiliaryUnits", AuxiliaryUnitsArray);

        PlayersArray.Add(MakeShareable(new FJsonValueObject(PlayerData)));
    }

    // Add players array to main JSON object
    SingleplayerMatchData->SetArrayField("Players", PlayersArray);

    // Serialize to string
    FString OutputString;
    TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
        TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&OutputString);
    FJsonSerializer::Serialize(SingleplayerMatchData.ToSharedRef(), Writer);

    // Save to file
    FString FilePath = FPaths::ProjectContentDir() / TEXT("Data/MatchGenFiles/SingleplayerMatchData.json");
    
    return FFileHelper::SaveStringToFile(OutputString, *FilePath);
}
