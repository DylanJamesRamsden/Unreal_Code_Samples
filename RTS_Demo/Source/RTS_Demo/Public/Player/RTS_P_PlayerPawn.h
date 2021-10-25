// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/Player/RTS_TroopSelectionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Player/RTS_CameraMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"

#include "RTS_P_PlayerPawn.generated.h"

UCLASS()
class RTS_DEMO_API ARTS_P_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTS_P_PlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//*******
	////Properties
	//*******

	UPROPERTY(EditAnywhere, Category = "RTS Spring Arm:")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "RTS Spring Arm:")
	USpringArmComponent* CameraSpring;

	UPROPERTY(EditAnywhere, Category = "RTS Camera:")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "RTS Camera:")
	URTS_CameraMovementComponent* RTS_CameraMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Functionality:")
	bool bCameraMovementEnabled;

	UPROPERTY(EditAnywhere, Category = "RTS Camera:")
	URTS_TroopSelectionComponent* RTS_TroopSelectionComponent;

	UPROPERTY(EditAnywhere, Category = "Functionality:")
	bool bTroopSelectionEnabled ;
	
	UPROPERTY(EditAnywhere, Category = "RTS Camera:|Zoom:")
	float ZoomAmount;
	UPROPERTY(EditAnywhere, Category = "RTS Camera:|Zoom:")
	float ZoomInterpAmount;
	UPROPERTY(EditAnywhere, Category = "RTS Camera:|Zoom:")
	float MinZoomDistance;
	UPROPERTY(EditAnywhere, Category = "RTS Camera:|Zoom:")
	float MaxZoomDistance;

	float TargetZoom;

	//*******
	////FUNCTIONS
	//*******

	void CameraZoom(float Value);
	
	void ComponentInitialization() const;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	URTS_TroopSelectionComponent* GetTroopSelectionComponent() const;

private:

	void CameraZoomTick(float DeltaTime);
};
