// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FireflyManager.h"
#include "GameFramework/Actor.h"
#include "GJFireflyJar.generated.h"

UCLASS()
class INTERCAMPUSGJ_2021_API AGJFireflyJar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGJFireflyJar();

	int CurrentFireFliesCaught = 0;

	AFireflyManager* Manager;

	void FireflyDistanceCheck();

	bool JarCollisionCheck(FVector Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Firefly Attributes|Behaviour")
	int NumberOfFireFliesToComplete = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Behaviour")
	float DistanceToEngage = 20.0;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Behaviour")
	FVector EntryPoint;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Firefly Attributes|Behaviour")
	FVector	 CenterPoint;

	UFUNCTION(BlueprintCallable, Category = "Firefly Attributes|Behaviour")
	void AddFireflyToJar();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Firefly Attributes|Behaviour")
	int GetFirefliesCaught();

	UFUNCTION(BlueprintNativeEvent, Category = "GJPlayer|World")
	void LevelComplete();
};
