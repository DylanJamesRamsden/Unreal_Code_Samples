// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Base/RTS_ActorComponent.h"

#include "RTS_CameraMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_DEMO_API URTS_CameraMovementComponent : public URTS_ActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTS_CameraMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "RTS Camera:|Movement:")
    float MovementSpeed;
    UPROPERTY(EditAnywhere, Category = "RTS Camera:|Movement:")
    bool EnableCameraBoundaries;
    UPROPERTY(EditAnywhere, Category = "RTS Camera:|Movement:", meta=(EditCondition="EnableCameraBoundaries"))
    FVector BoundaryOrigin;
    UPROPERTY(EditAnywhere, Category = "RTS Camera:|Movement:", meta=(EditCondition="EnableCameraBoundaries"))
    FVector BoundarySize;
    
    UPROPERTY(EditAnywhere, Category = "RTS Camera:|Rotation:")
    float RotationSpeed;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector MovementDirection;

	float TargetZoom;

	//Moves the pawn (forwards and backwards)
	void MoveCameraForward(float Value);

	//Moves the pawn (right and left)
	void MoveCameraRight(float Value);

	//Rotates the pawn (clockwise and anti-clockwise)
	void RotateCamera(float Value);

	void CameraMouseMovement(float DeltaTime);

	void CameraKeyboardMovement(float DeltaTime, AActor* TargetActor);
	
	virtual void BindComponentInput(UInputComponent* PlayerInputComponent) override;
};
