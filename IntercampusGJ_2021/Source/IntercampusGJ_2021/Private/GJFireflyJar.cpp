// Fill out your copyright notice in the Description page of Project Settings.


#include "GJFireflyJar.h"

#include "IntercampusGJ_2021/IntercampusGJ_2021.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGJFireflyJar::AGJFireflyJar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGJFireflyJar::FireflyDistanceCheck()
{
	for (auto Firefly : (Manager->GetFireFliesInWorld()))
	{
		if (FVector::Distance(Firefly->GetActorLocation(), this->GetActorLocation()) < DistanceToEngage && !Firefly->GetIsFoundByJar() && !JarCollisionCheck(Firefly->GetActorLocation()))
		{
			FVector JarLocationPoint = UKismetMathLibrary::RandomPointInBoundingBox(CenterPoint, FVector(20.0, 20.0, 15.0));
			Firefly->SetFoundByJar(true, EntryPoint, JarLocationPoint);
		}
	}
}

bool AGJFireflyJar::JarCollisionCheck(FVector Target)
{
	bool CollisionHit = false;
	
	FHitResult Hit;
	if (GetWorld())
	{
		CollisionHit = GetWorld()->LineTraceSingleByChannel(Hit,GetActorLocation(), Target, TRACE_ROOMWALL,
			FCollisionQueryParams(), FCollisionResponseParams());
	}

	return CollisionHit;
}

// Called when the game starts or when spawned
void AGJFireflyJar::BeginPlay()
{
	Super::BeginPlay();

	//Gets the Firefly Manager in the level
	if (UGameplayStatics::GetActorOfClass(this, AFireflyManager::StaticClass()))
	{
		if (Cast<AFireflyManager>(UGameplayStatics::GetActorOfClass(this, AFireflyManager::StaticClass())))
		{
			Manager = Cast<AFireflyManager>(UGameplayStatics::GetActorOfClass(this, AFireflyManager::StaticClass()));
		}
	}
}

// Called every frame
void AGJFireflyJar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireflyDistanceCheck();
}

void AGJFireflyJar::AddFireflyToJar()
{
	CurrentFireFliesCaught++;

	if (CurrentFireFliesCaught == NumberOfFireFliesToComplete)
	{
		LevelComplete();
	}
}

int AGJFireflyJar::GetFirefliesCaught()
{
	return CurrentFireFliesCaught;
}

void AGJFireflyJar::LevelComplete_Implementation()
{
}

