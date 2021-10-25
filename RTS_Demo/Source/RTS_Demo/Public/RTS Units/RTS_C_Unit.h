// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTS_P_Unit.h"

#include "RTS_C_Unit.generated.h"

/**
 * 
 */
UCLASS()
class RTS_DEMO_API ARTS_C_Unit : public AAIController
{
	GENERATED_BODY()

	public:

	ARTS_C_Unit();

	protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	ARTS_P_Unit* ControlledCharacter;
    
	//Movement
	UPROPERTY()
	bool bLocationSet = false;
    
	FVector TargetLocation;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SelectUnit();

	void UnselectUnit();

	void SetTargetLocation(FVector Location);

	FVector GetTargetLocation() const;

	void SetBLocationSet(bool IsSet);

	bool GetBLocationSet() const;

	bool IsAtTargetLocation() const;
	
};
