// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Enums/EResource.h"

#include "SUnitInfo.generated.h"

USTRUCT(BlueprintType)
struct FSUnitInfo : public FTableRowBase
{
   GENERATED_BODY()

   UPROPERTY(EditAnywhere, Category = "Game")
   FString UnitName;
   
   UPROPERTY(EditAnywhere, Category = "Game")
   float StartingHP;

   UPROPERTY(EditAnywhere, Category = "Game")
   float MaxHP;
   
   UPROPERTY(EditAnywhere, Category = "Game")
   float AttackDamage;
   
   UPROPERTY(EditAnywhere, Category = "Game")
   float AttackSpeed;

   UPROPERTY(EditAnywhere, Category = "Game")
   float Armor;

   UPROPERTY(EditAnywhere, Category = "Game")
   float MovementSpeed;

   UPROPERTY(EditAnywhere, Category = "Training")
   TMap<TEnumAsByte<EResource>, float> Cost;
   
   UPROPERTY(EditAnywhere, Category = "Trainng")
   float TrainTime;

   UPROPERTY(EditAnywhere, Category = "UI")
   UTexture2D* Icon;
};
