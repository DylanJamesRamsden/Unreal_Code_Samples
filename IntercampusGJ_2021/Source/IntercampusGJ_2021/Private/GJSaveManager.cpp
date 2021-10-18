// Fill out your copyright notice in the Description page of Project Settings.


#include "GJSaveManager.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AGJSaveManager::AGJSaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGJSaveManager::BeginPlay()
{
	Super::BeginPlay();

	SavedGame = LoadSavedGame();
}

// Called every frame
void AGJSaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UGJSaveGameTemplate* AGJSaveManager::LoadSavedGame()
{
	UGJSaveGameTemplate* LoadedGame = Cast<UGJSaveGameTemplate>(UGameplayStatics::LoadGameFromSlot("SaveSlot1", 0));

	if (LoadedGame)
	{
		return LoadedGame;
	}
	
	return CreateEmptyGame();
}

void AGJSaveManager::SaveLevelCompleted(const FString& LevelCompleted)
{
	SavedGame = LoadSavedGame();
	
	if (SavedGame)
	{

		if (LevelCompleted == "PuzzleOne")
		{
			SavedGame->Level1Complete = 1;
		}
		else 	if (LevelCompleted == "PuzzleTwo")
		{
			SavedGame->Level2Complete = 1;
		}
		else 	if (LevelCompleted == "PuzzleThree")
		{
			SavedGame->Level3Complete = 1;
		}
		else if (LevelCompleted == "PuzzleFour")
		{
			SavedGame->Level4Complete = 1;
		}
		else 	if (LevelCompleted == "PuzzleFive")
		{
			SavedGame->Level5Complete = 1;
		}
		else 	if (LevelCompleted == "PuzzleSix")
		{
			SavedGame->Level6Complete = 1;
		}
		else 	if (LevelCompleted == "PuzzleSeven")
		{
			SavedGame->Level7Complete = 1;
		}
		else 	if (LevelCompleted == "PuzzleEight")
		{
			SavedGame->Level8Complete = 1;
		}

		UGameplayStatics::SaveGameToSlot(SavedGame, "SaveSlot1", SavedGame->UserIndex);
	}
}

bool AGJSaveManager::CheckIfLevelIsComplete(int LevelCompleted)
{
	//UGJSaveGameTemplate* LoadedGame = LoadSavedGame();

	switch (LevelCompleted)
	{
	case 1:
		if (SavedGame->Level1Complete == 1)
		{
			return true;
		}
		return false;
		break;
	case 2:
		if (SavedGame->Level2Complete == 1)
		{
			return true;
		}
		return false;
		break;
	case 3:
		if (SavedGame->Level3Complete == 1)
		{
			return true;
		}
		return false;
		break;
	case 4:
		if (SavedGame->Level4Complete == 1)
		{
			return true;
		}
		return false;
		break;
	case 5:
		if (SavedGame->Level5Complete == 1)
		{
			return true;
		}
		return false;
		break;
	case 6:
		if (SavedGame->Level6Complete == 1)
		{
			return true;
		}
		return false;
		break;
	case 7:
		if (SavedGame->Level7Complete == 1)
		{
			return true;
		}
		return false;
		break;
	case 8:
		if (SavedGame->Level8Complete == 1)
		{
			return true;
		}
		return false;
		break;
	}

	return false;
}

UGJSaveGameTemplate* AGJSaveManager::CreateEmptyGame()
{
	UGJSaveGameTemplate* EmptySaveGame = Cast<UGJSaveGameTemplate>(UGameplayStatics::CreateSaveGameObject(UGJSaveGameTemplate::StaticClass()));

	return EmptySaveGame;
	
	//UGameplayStatics::SaveGameToSlot(EmptySaveGame, "SaveSlot1", 0);
}

