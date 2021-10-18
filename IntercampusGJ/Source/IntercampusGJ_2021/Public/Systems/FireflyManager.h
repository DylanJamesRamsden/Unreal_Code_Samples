// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GJFirefly.h"
#include "GameFramework/Actor.h"
#include "FireflyManager.generated.h"

UCLASS()
class INTERCAMPUSGJ_2021_API AFireflyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireflyManager();

private:
	TArray<AGJFirefly*> FirefliesControlled;
	TArray<AGJFirefly*> FirefliesInWorld;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GJPlayer|World")
	void AddControlledFirefly(AGJFirefly* Firefly);
	
	UFUNCTION(BlueprintCallable, Category = "GJPlayer|World")
	void RemoveControlledFirefly(AGJFirefly* Firefly);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "GJPlayer|World")
	int GetNumberOfControlledFireflies();

	UFUNCTION(BlueprintCallable, Category = "GJPlayer|World")
	void RemoveAllControlledFireflies();

	UFUNCTION(BlueprintCallable, Category = "GJPlayer|World")
	TArray<AGJFirefly*> GetFireFliesInWorld();
};
