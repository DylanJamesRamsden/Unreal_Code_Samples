// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTS_WaypointBanner.generated.h"

UCLASS()
class RTS_DEMO_API ARTS_WaypointBanner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTS_WaypointBanner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "RTS Spring Arm:")
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "RTS Spring Arm:")
	USkeletalMeshComponent* BannerMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
