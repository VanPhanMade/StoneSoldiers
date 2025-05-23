/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/

#include "GameInstanceSubsystems/MultiplayerSessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"

UMultiplayerSessionSubsystem::UMultiplayerSessionSubsystem() :
    CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
    FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
    JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
    DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
    StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete)),
    UpdateSessionCompleteDelegate(FOnUpdateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnUpdateSessionCompleted))
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if(Subsystem)
    {
        SessionInterface = Online::GetSessionInterface(GetWorld());
        if(GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Found subsystem %s "), *Subsystem->GetSubsystemName().ToString()));
		}
    }
    else
    {
        if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("No multiplayer subsystem detected!")));
		}
    }
}

void UMultiplayerSessionSubsystem::CreateSession(UObject* WorldContextObject, const TArray<FSessionPropertyKeyPair>& ExtraSettings, class APlayerController* PlayerController, int32 PublicConnections, int32 PrivateConnections, bool bUseLAN, bool bAllowInvites, bool bIsDedicatedServer, bool bUsePresence, bool bUseLobbiesIfAvailable, bool bAllowJoinViaPresence, bool bAllowJoinViaPresenceFriendsOnly, bool bAntiCheatProtected, bool bUsesStats, bool bShouldAdvertise, bool bUseLobbiesVoiceChatIfAvailable, bool bStartAfterCreate)
{
    if(!SessionInterface.IsValid()) return MultiplayerOnCreateSessionComplete.Broadcast(false);

    CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

    auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
    if(ExistingSession != nullptr)
    {
        bCreateSessionDestroy = true;
        LastNumPublicConnections = PublicConnections;
        LastMatchType = FString("FFA");
        DestroySession();
    }

    LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
    FOnlineSessionSettings Settings;
	LastSessionSettings->NumPublicConnections = PublicConnections;
	LastSessionSettings->NumPrivateConnections = PrivateConnections;
    LastSessionSettings->bShouldAdvertise = bShouldAdvertise;
    LastSessionSettings->bAllowJoinInProgress = true;
    LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : bUseLAN;
    LastSessionSettings->bAllowJoinViaPresence = bAllowJoinViaPresence;
    LastSessionSettings->bIsDedicated = bIsDedicatedServer;

    LastSessionSettings->bUsesPresence = bIsDedicatedServer ? false : bUsePresence;
    LastSessionSettings->bUseLobbiesIfAvailable = bIsDedicatedServer ? false: bUseLobbiesIfAvailable;

    LastSessionSettings->bUseLobbiesVoiceChatIfAvailable = bUseLobbiesIfAvailable ? bUseLobbiesVoiceChatIfAvailable : false;
    LastSessionSettings->bAllowJoinViaPresenceFriendsOnly = bAllowJoinViaPresenceFriendsOnly;
    LastSessionSettings->bAntiCheatProtected = bAntiCheatProtected;
    LastSessionSettings->bUsesStats = bUsesStats;

	LastSessionSettings->bAllowInvites = bAllowInvites;
	
    FOnlineSessionSetting ExtraSetting;
    for (int i = 0; i < ExtraSettings.Num(); i++)
    {
        ExtraSetting.Data = ExtraSettings[i].Data;
        //	ViaOnlineServiceAndPing
        ExtraSetting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
        Settings.Settings.Add(ExtraSettings[i].Key, ExtraSetting);
    }

    LastSessionSettings->BuildUniqueId = 1;
    LastSessionSettings->Set(FName("MatchType"), LastMatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings);
}

void UMultiplayerSessionSubsystem::FindSessions(int32 MaxSearchResults)
{
    if(!SessionInterface.IsValid()) return MultiplayerOnFindSessionsComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
    
    FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);
    
    LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
    LastSessionSearch->MaxSearchResults = MaxSearchResults;
    LastSessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
    LastSessionSearch->QuerySettings.Set(FName(TEXT("SEARCH_PRESENCE")), true, EOnlineComparisonOp::Equals);

    const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef());
}

void UMultiplayerSessionSubsystem::JoinSession(const FOnlineSessionSearchResult &SessionResult)
{
    if(!SessionInterface.IsValid()) return MultiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);

    JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
    
    const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

    if(&SessionResult != nullptr)
    {
        SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("My session result is null!")));
    }
}

void UMultiplayerSessionSubsystem::DestroySession()
{
    if(!SessionInterface.IsValid()) return MultiplayerOnDestroySessionComplete.Broadcast(false);

    DestroySessionCompleteDelegateHandle = SessionInterface->AddOnEndSessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);
    SessionInterface->DestroySession(NAME_GameSession);
}

void UMultiplayerSessionSubsystem::StartSession()
{
    if(!SessionInterface.IsValid()) return MultiplayerOnStartSessionComplete.Broadcast(false);

    StartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegate);

    SessionInterface->StartSession(NAME_GameSession);
}

void UMultiplayerSessionSubsystem::UpdateSession()
{
	if (!SessionInterface.IsValid()) return MultiplayerOnUpdateSessionComplete.Broadcast(false);

    UpdatedSessionSettings = MakeShareable(new FOnlineSessionSettings(*LastSessionSettings));
    // UpdatedSessionSettings->Set(FName("MatchType"), LastMatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    UpdateSessionCompleteDelegateHandle = SessionInterface->AddOnUpdateSessionCompleteDelegate_Handle(UpdateSessionCompleteDelegate);

    SessionInterface->UpdateSession(NAME_GameSession, *UpdatedSessionSettings);
}

void UMultiplayerSessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if(!SessionInterface) return;
    SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
    MultiplayerOnCreateSessionComplete.Broadcast(bWasSuccessful);

    if(bWasSuccessful)
    {
        UWorld* World = GetWorld();
        if(World)
        {
            if(GEngine)
            {
                GEngine->AddOnScreenDebugMessage( -1, 15.f, FColor::Yellow, FString::Printf(TEXT("Traveling to lobby.")));
                World->ServerTravel(FString("/Game/Levels/UnitSelectionLevels/UnitSelectionMultiplayer?listen"));
            }
        }
    }
    else
    {
        if(GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Failed to create a session.")));
        }
    }
}

void UMultiplayerSessionSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
    if(!SessionInterface.IsValid()) return;
    SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
    
    if(LastSessionSearch->SearchResults.Num() == 0) 
    {
        if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("Session results equal 0!")));
		}
        MultiplayerOnFindSessionsComplete.Broadcast(LastSessionSearch->SearchResults, false);
        return;
    }

    MultiplayerOnFindSessionsComplete.Broadcast(LastSessionSearch->SearchResults, bWasSuccessful);
    
}

void UMultiplayerSessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if(!SessionInterface.IsValid()) return;
    SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
    MultiplayerOnJoinSessionComplete.Broadcast(Result);
}

void UMultiplayerSessionSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
    if(!SessionInterface.IsValid()) return;
    SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
    MultiplayerOnDestroySessionComplete.Broadcast(bWasSuccessful);

    if(bWasSuccessful && bCreateSessionDestroy)
    {
        bCreateSessionDestroy = false;
        // CreateSession(LastNumPublicConnections, LastMatchType, false);
    }
}

void UMultiplayerSessionSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
    MultiplayerOnStartSessionComplete.Broadcast(bWasSuccessful);
    SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);

    UWorld* World = GetWorld();
    if(World) World->ServerTravel(FString("/Game/Levels/UnitSelectionLevels/UnitSelectionMultiplayer?listen"), true);
}

void UMultiplayerSessionSubsystem::OnUpdateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
    if(!SessionInterface.IsValid()) return MultiplayerOnUpdateSessionComplete.Broadcast(false);
    SessionInterface->ClearOnUpdateSessionCompleteDelegate_Handle(UpdateSessionCompleteDelegateHandle);

    if(bWasSuccessful)
    {
        LastSessionSettings = UpdatedSessionSettings;
        MultiplayerOnUpdateSessionComplete.Broadcast(bWasSuccessful);
    }
    else
    {
        MultiplayerOnUpdateSessionComplete.Broadcast(false);
    }
}

bool UMultiplayerSessionSubsystem::TryTravelToCurrentSession()
{

	return true;
}

