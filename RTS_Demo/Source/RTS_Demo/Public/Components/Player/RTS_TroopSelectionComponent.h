// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Base/RTS_ActorComponent.h"
#include "RTS Units/RTS_C_Unit.h"
#include "World/RTS_WaypointBanner.h"

#include "RTS_TroopSelectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_DEMO_API URTS_TroopSelectionComponent : public URTS_ActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTS_TroopSelectionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<ARTS_C_Unit*> SelectedUnits;

	//TEMP
	UPROPERTY(EditAnywhere, Category = "Troop Component|Visuals:")
	TSubclassOf<ARTS_WaypointBanner> UnitBannerToSpawn;

	UPROPERTY()
	TArray<ARTS_WaypointBanner*> UnitWaypointBanners;

	//UPROPERTY()
	//FTargetLocationSetSignature UnitTargetLocationSet;

	void WaypointBannerRaycast();

	void SpawnWaypointBanner(FVector Location, FRotator Rotation);

	bool DoesWaypointBannerExist(FVector Location);

	void DestroyOldWaypointBanner(FVector OldTargetLocation);

	void ClearAllUnitWaypointBanners();

	//void TestDelegate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddSelectedUnit(ARTS_C_Unit* SelectedUnit);

	void ClearSelectedUnits();
	
	virtual void BindComponentInput(UInputComponent* PlayerInputComponent) override;
};
