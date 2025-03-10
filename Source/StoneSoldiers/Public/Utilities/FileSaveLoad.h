// ©Van Phan

#pragma once

#include "CoreMinimal.h"

// Manager for loading and saving any files related to the game
// The first file I will be working with is the JSON file containing all the information for the maps
// Will want a function for grabbing any file I think, then a function for treating that file as a JSON file
// That said, looking at the reference video it may end up being that there is one function for each type of file we want to load in
// I.E. I may want a function for loading in JSON and I may want a function for loading and saving into binary

/**
 * 
 */
class STONESOLDIERS_API FileSaveLoad
{
public:
	FileSaveLoad();
	~FileSaveLoad();

	static FString ReadStringFromFile(FString FilePath);
	static TSharedPtr<FJsonObject> ReadJSON(FString JsonFilePath);
};
