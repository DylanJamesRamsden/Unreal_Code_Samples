// Fill out your copyright notice in the Description page of Project Settings.


#include "GJPlayerPawn.h"

#include "FireflyManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGJPlayerPawn::AGJPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGJPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGJPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGJPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	FireflyManager = Cast<AFireflyManager>(UGameplayStatics::GetActorOfClass(this, AFireflyManager::StaticClass()));
	PlayerInputComponent->BindAction("Deselect", IE_Pressed, FireflyManager, &AFireflyManager::RemoveAllControlledFireflies);
}

