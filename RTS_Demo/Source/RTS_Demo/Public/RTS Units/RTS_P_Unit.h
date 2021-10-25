// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "RTS_P_Unit.generated.h"

UCLASS()
class RTS_DEMO_API ARTS_P_Unit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTS_P_Unit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UDecalComponent* SelectionDecal;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HideSelectionDecal();

	void ShowSelectionDecal();
};
