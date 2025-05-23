/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/MultiplayerSessionsUI.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "GameInstanceSubsystems/MultiplayerSessionSubsystem.h"
#include "Widgets/Components/SessionDataUI.h"

bool UMultiplayerSessionsUI::Initialize()
{
    if(!Super::Initialize()) return false;

    if(BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &ThisClass::BackButtonClicked);
    }
    if(TryHostSessionButton)
    {
        TryHostSessionButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
    }

    if(HostSettingsOverlay)
    {
        HostSettingsOverlay->SetVisibility(ESlateVisibility::Collapsed);
    }

    if(CancelHostButton)
    {
        CancelHostButton->OnClicked.AddDynamic(this, &ThisClass::HostCancelButtonClicked);
    }

    if(ConfirmHostButton)
    {
        ConfirmHostButton->OnClicked.AddDynamic(this, &ThisClass::HostConfirmButtonClicked);
    }

    if(RefreshSessionsButton)
    {
        RefreshSessionsButton->OnClicked.AddDynamic(this, &ThisClass::RefreshSessionsList);
        UGameInstance* GameInstance = GetGameInstance();
        if(GameInstance)
        {
            UMultiplayerSessionSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
            if(Subsystem)
            {
                Subsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
            }
        }
    }

    return true;
}

void UMultiplayerSessionsUI::BackButtonClicked()
{
    OnBackButtonClicked.Broadcast();
}

void UMultiplayerSessionsUI::HostButtonClicked()
{
    HostSettingsOverlay->SetVisibility(ESlateVisibility::Visible);
}

void UMultiplayerSessionsUI::HostConfirmButtonClicked()
{
    // UGameInstance* GameInstance = GetGameInstance();
    // APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    // if (!PlayerController)
    // {
    //     UE_LOG(LogTemp, Error, TEXT("PlayerController not found."));
    //     return;
    // }

    // // Example world context object (can be any valid UObject or AActor)
    // UObject* WorldContextObject = GetWorld();

    // // Create an array of extra settings (if needed)
    // TArray<FSessionPropertyKeyPair> ExtraSettings;

    // if(GameInstance)
    // {
    //     UMultiplayerSessionSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();

    //     Subsystem->CreateSession(
    //         WorldContextObject,
    //         ExtraSettings,
    //         PlayerController, // Optional PlayerController (pass NULL if not needed)
    //         100,     // Public Connections
    //         0,       // Private Connections
    //         IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false,   // Use LAN ( always LAN if testing from PIE)
    //         true,    // Allow Invites
    //         false,   // Dedicated Server
    //         true,    // Use Presence
    //         true,    // Use Lobbies If Available
    //         true,    // Allow Join Via Presence
    //         false,   // Allow Join Via Presence Friends Only
    //         false,   // Anti Cheat Protected
    //         false,   // Uses Stats
    //         true,    // Should Advertise
    //         false,   // Use Voice Chat If Available
    //         true     // Start After Create
    //     );
    // }
}

void UMultiplayerSessionsUI::HostCancelButtonClicked()
{
    HostSettingsOverlay->SetVisibility(ESlateVisibility::Collapsed);
}

void UMultiplayerSessionsUI::RefreshSessionsList()
{
    UGameInstance* GameInstance = GetGameInstance();
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController not found."));
        return;
    }

    // Example world context object (can be any valid UObject or AActor)
    UObject* WorldContextObject = GetWorld();

    // Create an array of extra settings (if needed)
    TArray<FSessionPropertyKeyPair> ExtraSettings;

    // if(SessionsAvailableList) SessionsAvailableList->ClearChildren();

    if(GameInstance)
    {
        UMultiplayerSessionSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
        if(SessionsAvailableList) SessionsAvailableList->ClearChildren();

        if(RefreshSessionsButton) RefreshSessionsButton->SetIsEnabled(false);

        if(Subsystem) Subsystem->FindSessions(100);
    }
}

void UMultiplayerSessionsUI::OnFindSessions(const TArray<FOnlineSessionSearchResult> &SessionResults, bool bWasSuccessful)
{
    if(RefreshSessionsButton) RefreshSessionsButton->SetIsEnabled(true);

    // for(auto SessionResult : SessionResults)
    // {
    //     USessionDataUI* SessionUI = CreateWidget<USessionDataUI>(GetWorld(), ServerSearchResultWidget);
    //     if(SessionsAvailableList) SessionsAvailableList->AddChild(SessionUI);
    // }
    
    if(bWasSuccessful == false || SessionResults.Num() == 0) 
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Sessions searched failed search list callback!")));
        return;
    }
}

void UMultiplayerSessionsUI::OnSessionCreatedSuccess()
{
    UE_LOG(LogTemp, Log, TEXT("Session successfully created."));
    // UGameplayStatics::OpenLevel(GetWorld(), FName("UnitSelectionMultiplayer"), true, FString("listen"));
}

void UMultiplayerSessionsUI::OnSessionCreatedFailure()
{
    UE_LOG(LogTemp, Error, TEXT("Failed to create session."));
}

