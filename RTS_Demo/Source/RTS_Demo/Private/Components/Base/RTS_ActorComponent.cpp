// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Base/RTS_ActorComponent.h"

// Sets default values for this component's properties
URTS_ActorComponent::URTS_ActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URTS_ActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URTS_ActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URTS_ActorComponent::Activate(bool bReset)
{
	bActive = true;
}

void URTS_ActorComponent::Deactivate()
{
	bActive = false;
}

void URTS_ActorComponent::BindComponentInput(UInputComponent* PlayerInputComponent)
{
}

