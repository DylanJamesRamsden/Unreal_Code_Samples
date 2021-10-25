// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RTS_P_PlayerPawn.h"
#include "GameFramework/PlayerController.h"
#include "RTS_C_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_DEMO_API ARTS_C_PlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	//CONSTRUCTOR
	ARTS_C_PlayerController();

	protected:
	virtual void BeginPlay() override;

	/*Sets up the input mode for the RTS mode. It essentially locks the camera to the viewport, whether it be for the game or UI.*/
	void SetupRTSInputMode();

	ARTS_P_PlayerPawn* CameraPawnRef;

	virtual void SetupInputComponent() override;
};
