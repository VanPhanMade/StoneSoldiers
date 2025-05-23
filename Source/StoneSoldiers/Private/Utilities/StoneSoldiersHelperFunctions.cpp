/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Utilities/StoneSoldiersHelperFunctions.h"

StoneSoldiersHelperFunctions::StoneSoldiersHelperFunctions()
{
    
}

StoneSoldiersHelperFunctions::~StoneSoldiersHelperFunctions()
{

}

void StoneSoldiersHelperFunctions::LogEngineMessage(const char *Message)
{
    if (GEngine)
    {
        FString ConvertedMessage = FString(ANSI_TO_TCHAR(Message));
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, ConvertedMessage);
    }
}

void StoneSoldiersHelperFunctions::LogEngineMessage(const wchar_t *Message)
{

    if (GEngine)
    {
        FString ConvertedMessage = FString(Message);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, ConvertedMessage);
    }

}

void StoneSoldiersHelperFunctions::LogEngineMessage(const FText &Message)
{
    if (GEngine)
    {
        FString ConvertedMessage = Message.ToString();
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, ConvertedMessage);
    }
}

void StoneSoldiersHelperFunctions::LogEngineMessage(const FName &Message)
{
    if (GEngine)
    {
        FString ConvertedMessage = Message.ToString();
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, ConvertedMessage);
    }
}

void StoneSoldiersHelperFunctions::LogEngineMessage(const FString &Message)
{
     if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);
    }
}
