// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GJSaveGameTemplate.h"
#include "GameFramework/Actor.h"
#include "GJSaveManager.generated.h"

UCLASS()
class INTERCAMPUSGJ_2021_API AGJSaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGJSaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UGJSaveGameTemplate* SavedGame;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	UGJSaveGameTemplate* LoadSavedGame();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	void SaveLevelCompleted(const FString& LevelCompleted);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	bool CheckIfLevelIsComplete(int LevelCompleted);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	UGJSaveGameTemplate*  CreateEmptyGame();
};
