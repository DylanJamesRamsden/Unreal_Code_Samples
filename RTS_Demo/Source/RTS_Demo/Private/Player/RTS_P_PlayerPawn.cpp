// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Demo/Public/Player/RTS_P_PlayerPawn.h"

#include "Kismet/GameplayStatics.h"
#include "Player/RTS_C_PlayerController.h"
#include "Player/HUDs/RTS_HUD_Game.h"
#include "RTS Units/RTS_C_Unit.h"
#include "RTS_Demo/RTS_Demo.h"

// Sets default values
ARTS_P_PlayerPawn::ARTS_P_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the root component for the pawn
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	//Creates a camera spring for the player controlled camera
	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Spring"));
	//Creates a camera that will be controlled by the player (RTS_C_PlayerController)
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("RTS Camera"));

	//Hierarchy creation
	RootComponent = Root;
	CameraSpring->SetupAttachment(Root);
	Camera->SetupAttachment(CameraSpring);

	RTS_CameraMovementComponent = CreateDefaultSubobject<URTS_CameraMovementComponent>(FName("Camera Movement Component"));	
	RTS_TroopSelectionComponent = CreateDefaultSubobject<URTS_TroopSelectionComponent>(FName("TroopSelectionComponent"));
}

// Called when the game starts or when spawned
void ARTS_P_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ARTS_P_PlayerPawn::CameraZoom(float Value)
{
	TargetZoom = FMath::Clamp(CameraSpring->TargetArmLength + (Value * ZoomAmount), MinZoomDistance, MaxZoomDistance);
}

void ARTS_P_PlayerPawn::ComponentInitialization() const
{
	if (!bCameraMovementEnabled)
	{
		RTS_CameraMovementComponent->Deactivate();
	}

	if (!bTroopSelectionEnabled)
	{
		RTS_TroopSelectionComponent->Deactivate();
	}
}

// Called every frame
void ARTS_P_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCameraMovementEnabled)
	{
		if (CameraSpring)
		{
			CameraSpring->TargetArmLength = FMath::FInterpTo(CameraSpring->TargetArmLength, TargetZoom, GetWorld()->DeltaTimeSeconds, ZoomInterpAmount);
			//CameraZoomTick(DeltaTime);	
		}	
	}
}

// Called to bind functionality to input
void ARTS_P_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ComponentInitialization();

	if (RTS_CameraMovementComponent)
	{
		RTS_CameraMovementComponent->BindComponentInput(PlayerInputComponent);

		if (CameraSpring)
		{
			//Binds CameraZoom method to the ZoomCam axis
			PlayerInputComponent->BindAxis(TEXT("ZoomCam"), this, &ARTS_P_PlayerPawn::CameraZoom);	
		}
	}

	if (RTS_TroopSelectionComponent)
	{
		RTS_TroopSelectionComponent->BindComponentInput(PlayerInputComponent);	
	}
}

URTS_TroopSelectionComponent* ARTS_P_PlayerPawn::GetTroopSelectionComponent() const
{
	return RTS_TroopSelectionComponent;
}

void ARTS_P_PlayerPawn::CameraZoomTick(float DeltaTime)
{
	if (CameraSpring)
	{
		if (CameraSpring->TargetArmLength != TargetZoom)
		{
			if (CameraSpring->TargetArmLength < TargetZoom)
			{
				CameraSpring->TargetArmLength += ZoomInterpAmount;
			}
			else if (CameraSpring->TargetArmLength > TargetZoom)
			{
				CameraSpring->TargetArmLength -= ZoomInterpAmount;
			}
		}	
	}
}

