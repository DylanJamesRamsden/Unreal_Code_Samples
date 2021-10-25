// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Player/RTS_TroopSelectionComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Player/RTS_C_PlayerController.h"
#include "Player/HUDs/RTS_HUD_Game.h"
#include "World/RTS_WaypointBanner.h"

// Sets default values for this component's properties
URTS_TroopSelectionComponent::URTS_TroopSelectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URTS_TroopSelectionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
}


void URTS_TroopSelectionComponent::SpawnWaypointBanner(FVector Location, FRotator Rotation)
{
	FActorSpawnParameters SpawnParams;
	ARTS_WaypointBanner* NewBanner = Cast<ARTS_WaypointBanner>(GetWorld()->SpawnActor<AActor>(UnitBannerToSpawn, Location, Rotation, SpawnParams));

	UnitWaypointBanners.Add(NewBanner);
}

bool URTS_TroopSelectionComponent::DoesWaypointBannerExist(FVector Location)
{
	bool bDoesExist = false;
	
	for (auto Banner : UnitWaypointBanners)
	{
		ARTS_WaypointBanner* WaypointBanner = Cast<ARTS_WaypointBanner>(Banner);
		if (WaypointBanner)
		{
			if (Location == WaypointBanner->GetActorLocation())
			{
				bDoesExist = true;
				break;
			}	
		}
	}

	return bDoesExist;
}

void URTS_TroopSelectionComponent::DestroyOldWaypointBanner(FVector OldTargetLocation)
{
    ARTS_WaypointBanner* OldBannerToDestroy = nullptr;
	
	for (int i = 0; i < UnitWaypointBanners.Num(); i++)
	{
		if (UnitWaypointBanners[i]->GetActorLocation() == OldTargetLocation)
		{
			OldBannerToDestroy = UnitWaypointBanners[i];
			UnitWaypointBanners.RemoveAt(i);
			break;
		}
	}

	if (OldBannerToDestroy)
	{
		OldBannerToDestroy->Destroy();
	}
}

void URTS_TroopSelectionComponent::ClearAllUnitWaypointBanners()
{
	while (UnitWaypointBanners.Num() > 0)
	{
		ARTS_WaypointBanner* CurrentBanner = UnitWaypointBanners.Pop(true);
		CurrentBanner->Destroy();
	}
}

// Called every frame
void URTS_TroopSelectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bActive)
	{
		
	}
}

void URTS_TroopSelectionComponent::AddSelectedUnit(ARTS_C_Unit* SelectedUnit)
{
	if (SelectedUnit)
	{
		SelectedUnit->SelectUnit();
		SelectedUnits.Add(SelectedUnit);

		if (!SelectedUnit->IsAtTargetLocation())
		{
			if (!DoesWaypointBannerExist(SelectedUnit->GetTargetLocation()))
			{
				if (SelectedUnit->GetBLocationSet())
				{
					SpawnWaypointBanner(SelectedUnit->GetTargetLocation(), FRotator(0, 90.0, 0));
				}
			}
		}
	}
}

void URTS_TroopSelectionComponent::ClearSelectedUnits()
{
	if (SelectedUnits.Num() > 0)
	{
		for (auto SelectedUnit : SelectedUnits)
		{
			SelectedUnit->UnselectUnit();
		}

		SelectedUnits.Empty();

		ClearAllUnitWaypointBanners();
	}
}

void URTS_TroopSelectionComponent::BindComponentInput(UInputComponent* PlayerInputComponent)
{
	if (bActive)
	{
		//Binds the player's drag to StartSelection in HUD_RTS_Game
		PlayerInputComponent->BindAction("LeftMouseClick",
			EInputEvent::IE_Pressed, Cast<ARTS_HUD_Game>(UGameplayStatics::GetPlayerController(this,0)->GetHUD()),
			&ARTS_HUD_Game::StartSelection);

		PlayerInputComponent->BindAction("LeftMouseClick",
			EInputEvent::IE_Released, Cast<ARTS_HUD_Game>(UGameplayStatics::GetPlayerController(this,0)->GetHUD()),
			&ARTS_HUD_Game::EndSelection);

		PlayerInputComponent->BindAction("RightMouseClick",
		EInputEvent::IE_Pressed, this,
		&URTS_TroopSelectionComponent::WaypointBannerRaycast);
	}
}

void URTS_TroopSelectionComponent::WaypointBannerRaycast()
{
	if (SelectedUnits.Num() > 0)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			ARTS_C_PlayerController* RTS_PlayerController = Cast<ARTS_C_PlayerController>(UGameplayStatics::GetPlayerController(World, 0));
			if (RTS_PlayerController)
			{
				float MouseX;
				float MouseY;
				RTS_PlayerController->GetMousePosition(MouseX, MouseY);

				FVector2D MousePosition(MouseX, MouseY);
				FHitResult HitResult;
				const bool TraceComplex = false;

				if (RTS_PlayerController->GetHitResultAtScreenPosition(MousePosition, ECC_WorldStatic, TraceComplex, HitResult))
				{
					if (HitResult.GetActor())
					{
						SpawnWaypointBanner(HitResult.Location, FRotator(0, 90.0, 0));

						if (SelectedUnits.Num() > 0)
						{
							for (auto U : SelectedUnits)
							{
								DestroyOldWaypointBanner(U->GetTargetLocation());
							
								U->SetBLocationSet(true);
								U->SetTargetLocation(HitResult.Location);	
							}	
						}
					}
				}
			}
		}
	}
}

