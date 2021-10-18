// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GJDoor.generated.h"

UCLASS()
class INTERCAMPUSGJ_2021_API AGJDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGJDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int ConnectedLightsFused = 0;
	bool Unlocked = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp Attributes|Connections")
	bool AllowLampConnection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lamp Attributes|Connections", meta=(EditCondition="AllowLampConnection"))
	TArray<int> ConnectionIDs;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Lamp Attributes|Animations")
	UAnimationAsset* OpenAnimation;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Lamp Attributes|Collision")
	UBoxComponent* DoorCollision;

	UFUNCTION(BlueprintCallable, Category = "Lamp Attributes|Animations")
	void OpenDoor();

	bool IsConnected(TArray<int> IDs);
};
