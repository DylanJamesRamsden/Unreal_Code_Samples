// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GJPlayerController.h"
#include "Enums/GJMoveDirection.h"
#include "GameFramework/Actor.h"
#include "GJFirefly.generated.h"

class AGJFireflyJar;
class AFireflyManager;

UCLASS()
class INTERCAMPUSGJ_2021_API AGJFirefly : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGJFirefly();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//General
	float CurrentSpeed = 0.0f;

	//Collision focused
	bool FireflyCollisionCheck(FVector Target);
	FVector WallCollisionPoint;
	bool WallBetweenPlayerAndFirefly = false;

	//Player focused
	bool FoundByPlayer = false;
	FVector TargetLocation;

	//Firefly Jar focused
	bool FoundByJar = false;
	FVector JarEntry;
	FVector JarTarget;
	bool ReachedJarEntryPoint = false;
	bool Obtained;

	//Lamp focused
	bool AttractedToLight = false;
	FVector LampEntry;
	bool ConsumedByLamp = false;

	AFireflyManager* FireflyManager;
	AGJFireflyJar* FireflyJar;

	AGJPlayerController* PlayerController;

	bool DistanceCheckFromSelfToPlayerMouse();
	bool DistanceCheckFromTargetToPlayerMouse();
	bool DistanceCheckFromSelfToTarget(FVector Target, float DistanceLeaneancy);

	TEnumAsByte<EGJMoveDirection> GetDirectionToMove();

	USkeletalMeshComponent* FireflyMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*How fast the firefly follows the player's mouse*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Speed")
	float FollowSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Speed")
	float RotationSpeed;

	/*The tick at which the firefly updates and checks its distance from the player*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Behaviour")
	float DistanceToBeFound;

	/*The tick at which the firefly updates and checks its distance from the player*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Behaviour")
	FVector VariationFromPlayerMouse;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Behaviour")
	float MaxDistBetTargetAndPlayerLoc;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Behaviour")
	float MaxDistBetSelfAndTargetLoc;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Firefly Attributes|Colors")
	FColor LightColor;

	/*Gets the current speed of the firefly*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Firefly|Data")
	float GetCurrentSpeed();

	/*Gets whether or not the firefly has been found by the player*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Firefly|Data")
	bool GetIsFoundByPlayer();

	/*Gets whether or not the firefly has been found by the player*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Firefly|Data")
	bool GetIsFoundByJar();

	/*Gets whether or not the firefly has been found by the player*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Firefly|Data")
	bool GetIsAttractedToLight();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Firefly|Data")
	bool GetIsConsumedByLamp();

	UFUNCTION(BlueprintNativeEvent, Category = "Firefly|Behaviour")
	void InitiateFoundSequence();

	UFUNCTION(BlueprintCallable, Category = "Firefly|Data")
	void SetFoundByPlayer(bool Status);

	/*UFUNCTION(BlueprintCallable, Category = "Firefly|Data")
	void SetAttractedToLamp(bool Status, FVector LampEntryPoint);*/
	
	UFUNCTION(BlueprintCallable, Category = "Firefly|Data")
	void SetFoundByJar(bool Status, FVector JarEntryPoint, FVector JarTargetPoint);

	UFUNCTION(BlueprintCallable, Category = "Firefly|Data")
	bool SetAttractedToLamp(bool Status, FVector LampEntryPoint);

	/*//Collision focused
	UFUNCTION(BlueprintCallable, Category = "Firefly|Data")
	bool FireflyCollisionCheck();*/

	void FireflyBehaviour(AFireflyManager* Manager);

	void FireflyDeathBehaviour();

	UFUNCTION(BlueprintNativeEvent, Category = "Firefly|Data")
	void PlayDeathSound();
};
