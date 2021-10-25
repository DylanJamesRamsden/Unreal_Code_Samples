// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS Units/RTS_C_Unit.h"

#include "RTS Units/RTS_P_Unit.h"

// Sets default values
ARTS_C_Unit::ARTS_C_Unit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARTS_C_Unit::BeginPlay()
{
	Super::BeginPlay();

	ARTS_P_Unit* UnitPawn = Cast<ARTS_P_Unit>(GetPawn());
	if (UnitPawn)
	{
		ControlledCharacter = UnitPawn;	
	}
}

// Called every frame
void ARTS_C_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARTS_C_Unit::SelectUnit()
{
	if (ControlledCharacter)
	{
		ControlledCharacter->ShowSelectionDecal();
	}
}

void ARTS_C_Unit::UnselectUnit()
{
	if (ControlledCharacter)
	{
		ControlledCharacter->HideSelectionDecal();
	}
}

void ARTS_C_Unit::SetTargetLocation(FVector Location)
{
	TargetLocation = Location;
}

FVector ARTS_C_Unit::GetTargetLocation() const
{
	return TargetLocation;
}

void ARTS_C_Unit::SetBLocationSet(bool IsSet)
{
	bLocationSet = IsSet;
}

bool ARTS_C_Unit::GetBLocationSet() const
{
	return bLocationSet;
}

bool ARTS_C_Unit::IsAtTargetLocation() const
{
	if (FVector::Distance(GetPawn()->GetActorLocation(), TargetLocation) < 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

