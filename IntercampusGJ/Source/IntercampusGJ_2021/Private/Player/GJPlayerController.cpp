// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GJPlayerController.h"

FVector AGJPlayerController::GetPlayerMouseLocation()
{
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

	MouseWorldDirection = MouseWorldDirection * 550;
	MouseWorldLocation += MouseWorldDirection;
	MouseWorldLocation = FVector(MouseWorldLocation.X, 420.0, MouseWorldLocation.Z);

	return FVector(MouseWorldLocation.X, 420.0, MouseWorldLocation.Z);
}


