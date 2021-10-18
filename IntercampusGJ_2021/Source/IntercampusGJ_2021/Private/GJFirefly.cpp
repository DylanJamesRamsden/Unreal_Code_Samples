// Fill out your copyright notice in the Description page of Project Settings.


#include "GJFirefly.h"

#include "DrawDebugHelpers.h"
#include "FireflyManager.h"
#include "GJFireflyJar.h"
#include "IntercampusGJ_2021/IntercampusGJ_2021.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGJFirefly::AGJFirefly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGJFirefly::BeginPlay()
{
	Super::BeginPlay();
	
	//Get skeletal mesh of firefly (Move to BP)
	for (auto Child : this->GetComponents())
	{
		if (Cast<USkeletalMeshComponent>(Child))
		{
			FireflyMesh = Cast<USkeletalMeshComponent>(Child);
			break;
		}
	}

	FireflyJar = Cast<AGJFireflyJar>(UGameplayStatics::GetActorOfClass(this, AGJFireflyJar::StaticClass()));
	
	//Gets the player controller in the world
	PlayerController = Cast<AGJPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	RotationSpeed = FMath::FRandRange(RotationSpeed - 0.002, RotationSpeed + 0.002);
}

bool AGJFirefly::FireflyCollisionCheck(FVector Target)
{
	bool CollisionHit = false;
	
	FHitResult Hit;
	if (GetWorld())
	{
		CollisionHit = GetWorld()->LineTraceSingleByChannel(Hit,GetActorLocation(), Target, TRACE_ROOMWALL,
			FCollisionQueryParams(), FCollisionResponseParams());

		//WallBetweenPlayerAndFirefly = true;

		WallCollisionPoint = Hit.ImpactPoint;

		//(GetWorld(), GetActorLocation(), PlayerController->GetPlayerMouseLocation(), FColor::Red, false, 2, 0, 2);
	}

	WallBetweenPlayerAndFirefly = CollisionHit;
	return CollisionHit;
}

bool AGJFirefly::DistanceCheckFromSelfToPlayerMouse()
{
	bool IsCloseEnough = false;

	if (PlayerController)
	{
		if (FVector::Dist(PlayerController->GetPlayerMouseLocation(), this->GetActorLocation()) < DistanceToBeFound)
		{
			IsCloseEnough = true;
		}
	}

	return IsCloseEnough;
}

bool AGJFirefly::DistanceCheckFromTargetToPlayerMouse()
{
	bool IsCloseEnough = false;

	if (PlayerController)
	{
		if (FVector::Dist(PlayerController->GetPlayerMouseLocation(), TargetLocation) < MaxDistBetTargetAndPlayerLoc)
		{
			IsCloseEnough = true;
		}
	}

	return IsCloseEnough;
}

bool AGJFirefly::DistanceCheckFromSelfToTarget(FVector Target, float DistanceLeaneancy)
{
	bool IsCloseEnough = false;

	if (PlayerController)
	{
		if (FVector::Dist(GetActorLocation(), Target) < DistanceLeaneancy)
		{
			IsCloseEnough = true;
		}
	}

	return IsCloseEnough;
}

void AGJFirefly::FireflyBehaviour(AFireflyManager* Manager)
{
	if (!FireflyManager)
	{
		FireflyManager = Manager;
	}
	
	if (!Obtained && !AttractedToLight)
	{
		if (!FoundByJar)
		{
			if (FoundByPlayer)
			{
				//Collision handling
				FireflyCollisionCheck(PlayerController->GetPlayerMouseLocation());
				if (WallBetweenPlayerAndFirefly)
				{
					if (!DistanceCheckFromSelfToTarget(WallCollisionPoint, 10))
					{
						//Add some variation to the follow speed
						//CurrentSpeed = FMath::FRandRange(FollowSpeed - 0.002, FollowSpeed + 0.002);
					
						SetActorLocation(FMath::Lerp(GetActorLocation(), WallCollisionPoint, CurrentSpeed));
					}
					else
					{
						CurrentSpeed = 0;
					}
				}	
				//Check if the target location is close enough to the players mouse
				else if (DistanceCheckFromTargetToPlayerMouse())
				{
					if (!DistanceCheckFromSelfToTarget(TargetLocation, MaxDistBetSelfAndTargetLoc))
					{
						//Add some variation to the follow speed
						CurrentSpeed = FMath::FRandRange(FollowSpeed - 0.002, FollowSpeed + 0.002);
					
						SetActorLocation(FMath::Lerp(GetActorLocation(), TargetLocation, CurrentSpeed));
					}
					else
					{
						CurrentSpeed = 0;
					}
				}
				else
				{
					//Get a target location
					TargetLocation =  UKismetMathLibrary::RandomPointInBoundingBox(PlayerController->GetPlayerMouseLocation(), VariationFromPlayerMouse);
				}

				if (GetDirectionToMove() == Right)
				{
					if (GetActorRotation().Yaw != 0)
					{
						SetActorRotation(FMath::Lerp(GetActorRotation(), FRotator(0.0,0.0, 0.0), RotationSpeed));
					}
				}
				else if (GetDirectionToMove() == Left)
				{
					if (GetActorRotation().Yaw != 180)
					{
						SetActorRotation(FMath::Lerp(GetActorRotation(), FRotator(0.0,180.0, 0.0), RotationSpeed));
					}
				}	
			}
			else
			{
				if (DistanceCheckFromSelfToPlayerMouse())
				{
					//Set FoundByPlayer to true (meaning the firefly will now follow the players mouse)
					InitiateFoundSequence();
				
					FoundByPlayer = true;
					FireflyMesh->SetRenderCustomDepth(true);
					Manager->AddControlledFirefly(this);
					TargetLocation =  UKismetMathLibrary::RandomPointInBoundingBox(PlayerController->GetPlayerMouseLocation(), VariationFromPlayerMouse);
				}

				if (CurrentSpeed > 0)
				{
					//CurrentSpeed = 0;
					CurrentSpeed = FMath::Lerp(CurrentSpeed, 0.0f, 0.025f);
					SetActorLocation(FMath::Lerp(GetActorLocation(), TargetLocation, CurrentSpeed));
				}
			}
		}
		else
		{
			if (!ReachedJarEntryPoint) //Move to entry point
			{
				if (DistanceCheckFromSelfToTarget(JarEntry, 10))
				{
					ReachedJarEntryPoint = true;
				}
				else
				{
					//Move!!!!!
					//FireflyMesh->SetRenderCustomDepth(false);
					
					SetActorLocation(FMath::Lerp(GetActorLocation(), JarEntry, CurrentSpeed));
				}
			}
			else //Move to jar point
			{
				if (DistanceCheckFromSelfToTarget(JarTarget, 5))
				{
					Obtained = true;
					FireflyJar->AddFireflyToJar();
					
				}
				else
				{		
					SetActorLocation(FMath::Lerp(GetActorLocation(), JarTarget, CurrentSpeed));
				}
			}
		}
	}
	else if (AttractedToLight)
	{
		if (DistanceCheckFromSelfToTarget(LampEntry, 10))
		{
			ConsumedByLamp = true;
		}
		else
		{
			FireflyMesh->SetRenderCustomDepth(false);
			SetActorLocation(FMath::Lerp(GetActorLocation(), LampEntry, FollowSpeed * 2.5));
		}
	}
}

void AGJFirefly::FireflyDeathBehaviour()
{
	if (FireflyManager)
	{
		FireflyManager->RemoveControlledFirefly(this);
		PlayDeathSound();
		Destroy();
	}
}

void AGJFirefly::PlayDeathSound_Implementation()
{
}

TEnumAsByte<EGJMoveDirection> AGJFirefly::GetDirectionToMove()
{
	//Add in logic so it doesnt turn if the mouse is really close
	
	if (PlayerController->GetPlayerMouseLocation().X < GetActorLocation().X)
	{
		return Left;
	}
	else
	{
		return Right;
	}
}

// Called every frame
void AGJFirefly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AGJFirefly::GetCurrentSpeed()
{
	return CurrentSpeed;
}

bool AGJFirefly::GetIsFoundByPlayer()
{
	return FoundByPlayer;
}

bool AGJFirefly::GetIsFoundByJar()
{
	return FoundByJar;
}

bool AGJFirefly::GetIsAttractedToLight()
{
	return AttractedToLight;
}

bool AGJFirefly::GetIsConsumedByLamp()
{
	return ConsumedByLamp;
}

void AGJFirefly::SetFoundByPlayer(bool Status)
{
	FireflyMesh->SetRenderCustomDepth(Status);
	FoundByPlayer = Status;
}

void AGJFirefly::SetFoundByJar(bool Status, FVector JarEntryPoint, FVector JarTargetPoint)
{
	FoundByJar = true;
	this->JarEntry = JarEntryPoint;
	this->JarTarget = JarTargetPoint;
	FireflyMesh->SetRenderCustomDepth(false);
}

bool AGJFirefly::SetAttractedToLamp(bool Status, FVector LampEntryPoint)
{
	
	if (!Status)
	{
		AttractedToLight = false;
		FireflyMesh->SetRenderCustomDepth(true);

		return true;
	}
	else
	{
		if (!FireflyCollisionCheck(LampEntryPoint))
		{
			AttractedToLight = true;
			LampEntry = LampEntryPoint;
			return true;
		}

		return false;
	}
}

void AGJFirefly::InitiateFoundSequence_Implementation()
{
	
}

