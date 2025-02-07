// ©Van Phan

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STONESOLDIERS_API StoneSoldiersHelperFunctions
{
public:
	StoneSoldiersHelperFunctions();
	~StoneSoldiersHelperFunctions();

	static void LogEngineMessage(const char* Message);

	static void LogEngineMessage(const wchar_t* Message);

	static void LogEngineMessage(const FText& Message);

	static void LogEngineMessage(const FName& Message);

	static void LogEngineMessage(const FString& Message);

};
