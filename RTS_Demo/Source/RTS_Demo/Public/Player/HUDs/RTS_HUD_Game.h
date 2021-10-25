// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "I_RTS_SelectionBoxInterface.h"
#include "GameFramework/HUD.h"
#include "RTS_HUD_Game.generated.h"

/**
 * 
 */
UCLASS()
class RTS_DEMO_API ARTS_HUD_Game : public AHUD, public II_RTS_SelectionBoxInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Player UI", meta=(DisplyName="Enable Game UI"))
	bool bEnableGameUI;
	
	//protected:
	UPROPERTY(EditAnywhere, Category = "Player UI")
	TSubclassOf<UUserWidget> InGameUIToCreate;

	UPROPERTY()
	class UUserWidget* InGameUIInstance;

	FVector2D MouseStartPosition;

	FVector2D MouseCurrentPosition;

	bool IsDragging;

	public:

	virtual void StartSelection() override;

	virtual void EndSelection() override;

	virtual void DrawHUD() override;

	virtual void DragSelectUnits() override;
protected:
	virtual void BeginPlay() override;

	void CreatePlayerGameUI();
};
