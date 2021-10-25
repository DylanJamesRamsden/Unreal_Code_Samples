// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HUDs/RTS_HUD_Game.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RTS_C_PlayerController.h"

void ARTS_HUD_Game::StartSelection()
{
	FVector2D(UGameplayStatics::GetPlayerController(this, 0)->GetMousePosition(MouseStartPosition.X, MouseStartPosition.Y));

	IsDragging = true;
}

void ARTS_HUD_Game::EndSelection()
{
	IsDragging = false;
}

void ARTS_HUD_Game::DrawHUD()
{
	if (IsDragging)
	{
		ARTS_P_PlayerPawn* RTS_PlayerPawn = Cast<ARTS_P_PlayerPawn>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
		if (RTS_PlayerPawn)
		{
			URTS_TroopSelectionComponent* RTS_TroopSelectionComponent = RTS_PlayerPawn->GetTroopSelectionComponent();
			if (RTS_TroopSelectionComponent)
			{
				RTS_PlayerPawn->GetTroopSelectionComponent()->ClearSelectedUnits();
		
				FVector2D(UGameplayStatics::GetPlayerController(this, 0)->GetMousePosition(MouseCurrentPosition.X, MouseCurrentPosition.Y));

				const float ScreenX = MouseStartPosition.X;
				const float ScreenY = MouseStartPosition.Y;

				const float ScreenW = MouseCurrentPosition.X - ScreenX;
				const float ScreenH = MouseCurrentPosition.Y - ScreenY;
		
				DrawRect(FLinearColor(0, 0, 1, .15f), ScreenX, ScreenY, ScreenW, ScreenH);

				DragSelectUnits();		
			}
		}
	}
}

void ARTS_HUD_Game::DragSelectUnits()
{
	TArray<ARTS_P_Unit*> OutUnits;
	GetActorsInSelectionRectangle(FVector2D(MouseStartPosition.X, MouseStartPosition.Y), FVector2D(MouseCurrentPosition.X, MouseCurrentPosition.Y), OutUnits);

	ARTS_P_PlayerPawn* RTS_PlayerPawn = Cast<ARTS_P_PlayerPawn>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());
	if (RTS_PlayerPawn)
	{
		for (auto SelectedUnit : (OutUnits))
		{
			//U->SelectUnit();
			ARTS_C_Unit* UnitController = Cast<ARTS_C_Unit>(SelectedUnit->GetController());
			if (UnitController)
			{
				RTS_PlayerPawn->GetTroopSelectionComponent()->AddSelectedUnit(UnitController);	
			}
		}	
	}
}

void ARTS_HUD_Game::BeginPlay()
{
	CreatePlayerGameUI();
}

void ARTS_HUD_Game::CreatePlayerGameUI()
{
	if (bEnableGameUI)
	{
		if (InGameUIToCreate)
		{
			InGameUIInstance = Cast<UUserWidget>(CreateWidget(GetWorld(), InGameUIToCreate));

			if (InGameUIInstance)
			{
				InGameUIInstance->AddToViewport(1);
			}
		}
	}
}
