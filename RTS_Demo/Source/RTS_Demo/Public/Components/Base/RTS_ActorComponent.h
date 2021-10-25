// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTS_ActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_DEMO_API URTS_ActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTS_ActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bActive = true;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;

	virtual void BindComponentInput(UInputComponent* PlayerInputComponent);
};
