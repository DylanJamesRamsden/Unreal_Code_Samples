// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS Units/RTS_P_Unit.h"

// Sets default values
ARTS_P_Unit::ARTS_P_Unit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(RootComponent);

	SelectionDecal->SetVisibility(false);
}

// Called when the game starts or when spawned
void ARTS_P_Unit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTS_P_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARTS_P_Unit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARTS_P_Unit::HideSelectionDecal()
{
	SelectionDecal->SetVisibility(false); 
}

void ARTS_P_Unit::ShowSelectionDecal()
{
	SelectionDecal->SetVisibility(true); 
}

