// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/FireflyManager.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AFireflyManager::AFireflyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFireflyManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ActorsFound;
	UGameplayStatics::GetAllActorsOfClass(this, AGJFirefly::StaticClass(), ActorsFound);

	for (auto Found : ActorsFound)
	{
		if (Cast<AGJFirefly>(Found))
		{
			FirefliesInWorld.Add(Cast<AGJFirefly>(Found));
		}
	}
}

// Called every frame
void AFireflyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto FireFly : FirefliesInWorld)
	{
		//break up move logic
		FireFly->FireflyBehaviour(this);
	}
}

void AFireflyManager::AddControlledFirefly(AGJFirefly* Firefly)
{
	FirefliesControlled.Add(Firefly);
}

void AFireflyManager::RemoveControlledFirefly(AGJFirefly* Firefly)
{
	if (Firefly)
	{
		Firefly->SetFoundByPlayer(false);
		FirefliesInWorld.Remove(Firefly);
		FirefliesControlled.Remove(Firefly);	
	}
}

int AFireflyManager::GetNumberOfControlledFireflies()
{
	return FirefliesControlled.Num();
}

void AFireflyManager::RemoveAllControlledFireflies()
{
	for (auto Firefly : FirefliesInWorld)
	{
		Firefly->SetFoundByPlayer(false);
	}
}

TArray<AGJFirefly*> AFireflyManager::GetFireFliesInWorld()
{
	return FirefliesInWorld;
}
