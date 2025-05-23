/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Utilities/FileSaveLoad.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

#include "Serialization/JsonSerializer.h"

FileSaveLoad::FileSaveLoad()
{
}

FileSaveLoad::~FileSaveLoad()
{
}

FString FileSaveLoad::ReadStringFromFile(FString FilePath)
{
	// Checks that the file can be loaded
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("File Not Found");
		return "";
	}

	FString RetString = "";

	if (!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("Unable to read string from file.");
		return "";
	}
	
	return RetString;
}

TSharedPtr<FJsonObject> FileSaveLoad::ReadJSON(FString JsonFilePath)
{
	// Try to Read File
	FString JsonString = ReadStringFromFile(JsonFilePath);
	if (JsonString == "")
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("Unable to Read File");
		return nullptr;
	}

	TSharedPtr<FJsonObject> RetJsonObject;

	// Try to convert to JSON
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("Failed to Deserialize Json.");
		return nullptr;
	}

	return RetJsonObject;
}
