// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "GJPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class INTERCAMPUSGJ_2021_API AGJPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GJPlayer|World")
	FVector GetPlayerMouseLocation();
};
