// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RTS_C_PlayerController.h"
#include "Kismet/GameplayStatics.h"

ARTS_C_PlayerController::ARTS_C_PlayerController()
{
}

void ARTS_C_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	//SetupRTSInputMode();
	bShowMouseCursor = true;

	//CHANGE PLAYER INDEX FOR MULTIPLAYER
	CameraPawnRef = Cast<ARTS_P_PlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ARTS_C_PlayerController::SetupRTSInputMode()
{
	FInputModeGameAndUI RTSInputMode;
	RTSInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(RTSInputMode);
}

void ARTS_C_PlayerController::SetupInputComponent()
{
	
}
