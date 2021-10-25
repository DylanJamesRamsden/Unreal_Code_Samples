// Fill out your copyright notice in the Description page of Project Settings.


#include "World/RTS_WaypointBanner.h"

// Sets default values
ARTS_WaypointBanner::ARTS_WaypointBanner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the root component for the pawn
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));

	BannerMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Banner Mesh");

	RootComponent = Root;
	BannerMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ARTS_WaypointBanner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTS_WaypointBanner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

