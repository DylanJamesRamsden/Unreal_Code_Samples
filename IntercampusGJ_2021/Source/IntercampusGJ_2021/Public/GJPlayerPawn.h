// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FireflyManager.h"
#include "GameFramework/Pawn.h"
#include "GJPlayerPawn.generated.h"

UCLASS()
class INTERCAMPUSGJ_2021_API AGJPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGJPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AFireflyManager* FireflyManager;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
