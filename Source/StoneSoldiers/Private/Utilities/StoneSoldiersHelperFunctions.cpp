// ©Van Phan


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
        // Convert the const char* to FString
        FString ConvertedMessage = FString(ANSI_TO_TCHAR(Message));

        // Display the message on the screen
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, ConvertedMessage);
    }
}

void StoneSoldiersHelperFunctions::LogEngineMessage(const wchar_t *Message)
{
    if (GEngine)
    {
        // Convert the const wchar_t* to FString
        FString ConvertedMessage = FString(Message);

        // Display the message on the screen
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, ConvertedMessage);
    }

}
