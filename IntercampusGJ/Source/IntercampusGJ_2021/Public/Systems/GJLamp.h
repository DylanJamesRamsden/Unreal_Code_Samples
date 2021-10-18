// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FireflyManager.h"
#include "GJDoor.h"
#include "Components/SpotLightComponent.h"
#include "Enums/GJLampType.h"
#include "GameFramework/Actor.h"
#include "GJLamp.generated.h"

UCLASS()
class INTERCAMPUSGJ_2021_API AGJLamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGJLamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AFireflyManager* Manager;

	bool Fused = false;

	//OnOffLight
	float CurrentSwitchTimer;

	AGJFirefly* FireflyAttracting;
	bool AttractingFirefly = false;

	TArray<AGJDoor*> ConnectedDoors;

	void LightBehaviour();

	void LightFuseBehaviour(EGJLampType CheckType);

	void FindConnectedDoor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp Attributes")
	TEnumAsByte<EGJLampType> TypeOfLight = Constant;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Lamp Attributes|Behaviour")
	FVector DetectionPoint;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp Attributes|Connections")
	bool ConnectToDoor;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp Attributes|Connections", meta=(EditCondition="ConnectToDoor"))
	TArray<int> DoorIDs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp Attributes|OnOff Behaviour")
	float TimeToSwitch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp Attributes|Colors")
	bool AttractSpecificColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp Attributes|Colors", meta=(EditCondition="AttractSpecificColor"))
	FColor ColorToAttract;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Firefly|Data")
	float GetDegreeBetweenTwoPoints(FVector A, FVector B);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Lamp Attributes|Connections", meta=(EditCondition="ConnectToDoor"))
	USpotLightComponent* Spotlight;
};
