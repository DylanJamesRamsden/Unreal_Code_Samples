// Fill out your copyright notice in the Description page of Project Settings.


#include "GJLamp.h"

#include <ctime>

#include "Kismet/GameplayStatics.h"

// Sets default values
AGJLamp::AGJLamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGJLamp::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::GetActorOfClass(this, AFireflyManager::StaticClass()))
	{
		if (Cast<AFireflyManager>(UGameplayStatics::GetActorOfClass(this, AFireflyManager::StaticClass())))
		{
			Manager = Cast<AFireflyManager>(UGameplayStatics::GetActorOfClass(this, AFireflyManager::StaticClass()));
		}
	}

	FindConnectedDoor();
}

void AGJLamp::LightBehaviour()
{
	if (!Fused)
	{
		if (!AttractingFirefly)
		{
			for (auto Firefly : Manager->GetFireFliesInWorld())
			{
				//Rename Attracted to light to lamp
				if (!Firefly->GetIsAttractedToLight())
				{
					if (AttractSpecificColor)
					{
						if (Firefly->LightColor == ColorToAttract)
						{
							if (Firefly->GetActorLocation().Z < GetActorLocation().Z)
							{
								if (GetDegreeBetweenTwoPoints(DetectionPoint, Firefly->GetActorLocation()) <= 1.5 &&
								GetDegreeBetweenTwoPoints(DetectionPoint, Firefly->GetActorLocation()) >= -1.5)
								{
									if (Firefly->SetAttractedToLamp(true, this->DetectionPoint))
									{
										AttractingFirefly = true;
										FireflyAttracting = Firefly;
										break;
									}
								}
							}
						}
					}
					else
					{
						if (Firefly->GetActorLocation().Z < GetActorLocation().Z)
						{
							if (GetDegreeBetweenTwoPoints(DetectionPoint, Firefly->GetActorLocation()) <= 1.5 &&
							GetDegreeBetweenTwoPoints(DetectionPoint, Firefly->GetActorLocation()) >= -1.5)
							{
								if (Firefly->SetAttractedToLamp(true, this->DetectionPoint))
								{
									AttractingFirefly = true;
									FireflyAttracting = Firefly;
									break;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			if (FireflyAttracting->GetIsConsumedByLamp())
			{
				AttractingFirefly = false;
				FireflyAttracting->FireflyDeathBehaviour();
			
				FireflyAttracting = nullptr;
				//Kill firefly (and remove it from FireFliesInWorld)

				LightFuseBehaviour(Connected);
			}
		}
	}
}

void AGJLamp::LightFuseBehaviour(EGJLampType CheckType)
{
	if (CheckType == OnOff)
	{
		if (TypeOfLight == OnOff)
		{
			if (CurrentSwitchTimer < TimeToSwitch)
			{
				CurrentSwitchTimer += GetWorld()->GetDeltaSeconds();
			}
			else
			{
				CurrentSwitchTimer = 0;
				//Disable/Enable Light
				if (Fused)
				{
					Fused = false;

					Spotlight->SetVisibility(true);
				}
				else
				{
					Fused = true;

					Spotlight->SetVisibility(false);

					if (FireflyAttracting)
					{
						FireflyAttracting->SetAttractedToLamp(false, DetectionPoint);
					}

					AttractingFirefly = false;
				}
			}
		}
	}
	else if (CheckType == Connected)
	{
		if (TypeOfLight == Connected)
		{
			Fused = true;

			for (auto Door : ConnectedDoors)
			{
				Door->OpenDoor();
			}

			Spotlight->SetVisibility(false);
		}
	}
}

void AGJLamp::FindConnectedDoor()
{
	TArray<AActor*> DoorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(this, AGJDoor::StaticClass(), DoorsInWorld);

	for (auto Door : DoorsInWorld)
	{
		AGJDoor* CastedDoor = Cast<AGJDoor>(Door);

		//Change this
		if (CastedDoor->IsConnected(DoorIDs))
		{
			ConnectedDoors.Add(CastedDoor);
		}
	}
}

// Called every frame
void AGJLamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LightFuseBehaviour(OnOff);
	LightBehaviour();
}

float AGJLamp::GetDegreeBetweenTwoPoints(FVector A, FVector B)
{
	float Ang1 = FMath::Atan2(A.X, A.Y);
	float Ang2 = FMath::Atan2(B.X, B.Y);
	float Ang = FMath::RadiansToDegrees(Ang1 - Ang2);
	if(Ang > 180.0f) Ang -= 360.0f; else if(Ang < -180.0f) Ang += 360.0f;
	
	return Ang;
}

