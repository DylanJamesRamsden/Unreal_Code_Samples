// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Player/RTS_CameraMovementComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URTS_CameraMovementComponent::URTS_CameraMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	

	// ...
}


// Called when the game starts
void URTS_CameraMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void URTS_CameraMovementComponent::MoveCameraForward(float Value)
{
	//We look at X because that is forwards and backwards in Unreal
	MovementDirection.X = FMath::Clamp(Value, -1.0f, 1.0f);
}

void URTS_CameraMovementComponent::MoveCameraRight(float Value)
{
	//We look at Y because that is right and left in Unreal
	MovementDirection.Y = FMath::Clamp(Value, -1.0f, 1.0f);
}

void URTS_CameraMovementComponent::RotateCamera(float Value)
{
	if (Value == -1) //Rotate Left
	{
		
	}
	else if (Value == 1) //Rotate Right
	{
		
	}
}

// Called every frame
void URTS_CameraMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bActive)
	{
		CameraMouseMovement(DeltaTime);
		CameraKeyboardMovement(DeltaTime, GetOwner());		
	}
}

void URTS_CameraMovementComponent::CameraMouseMovement(float DeltaTime)
{
	float MouseX;
	float MouseY;

	int ViewportSizeX;
	int ViewportSizeY;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	PlayerController->GetMousePosition(MouseX, MouseY);
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	if (MouseX <= 50)
	{
		MoveCameraRight(-1);
	}

	if (MouseX >= ViewportSizeX - 50)
	{
		MoveCameraRight(11);
	}

	if (MouseY <= 50)
	{
		MoveCameraForward(1);
	}

	if (MouseY >= ViewportSizeY - 50)
	{
		MoveCameraForward(-1);
	}
}

void URTS_CameraMovementComponent::CameraKeyboardMovement(float DeltaTime, AActor* TargetActor)
{
	if (!MovementDirection.IsZero())
	{
		const FVector NewCameraLocation = TargetActor->GetActorLocation() + (MovementDirection * DeltaTime * MovementSpeed);
		TargetActor->SetActorLocation(NewCameraLocation);
	}
}

void URTS_CameraMovementComponent::BindComponentInput(UInputComponent* PlayerInputComponent)
{
	if (bActive)
	{
		//Binds MoveCameraForward method to the MoveForward axis
		PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &URTS_CameraMovementComponent::MoveCameraForward);
		//Binds MoveCameraRight method to the MoveRight axis
		PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &URTS_CameraMovementComponent::MoveCameraRight);
		//Binds RotateCamera method to the RotateCam axis
		PlayerInputComponent->BindAxis(TEXT("RotateCam"), this, &URTS_CameraMovementComponent::RotateCamera);		
	}
}

