// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "GJSaveGameTemplate.Generated.h"

/**
 * 
 */
UCLASS()
class INTERCAMPUSGJ_2021_API UGJSaveGameTemplate  : public USaveGame
{

	GENERATED_BODY()
	
public:
	UGJSaveGameTemplate();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

    UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level1Complete;
    UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level2Complete;
    UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level3Complete;
    UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level4Complete;
    UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level5Complete;
    UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level6Complete;
    UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level7Complete;
    UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level8Complete;
};
