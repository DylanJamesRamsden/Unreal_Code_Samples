// Fill out your copyright notice in the Description page of Project Settings.


#include "GJDoor.h"

#include "IntercampusGJ_2021/IntercampusGJ_2021.h"

// Sets default values
AGJDoor::AGJDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGJDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGJDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//USkeletalMesh::Materials[0] = 
}

void AGJDoor::OpenDoor()
{
	USkeletalMeshComponent* DoorMesh = Cast<USkeletalMeshComponent>(this->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	ConnectedLightsFused++;

	if (ConnectedLightsFused == ConnectionIDs.Num())
	{
		if (OpenAnimation)
		{
			DoorMesh->PlayAnimation(OpenAnimation, false);	
		}


		if (DoorCollision)
		{
			DoorCollision->SetCollisionResponseToChannel(TRACE_ROOMWALL,ECR_Ignore);	
		}
	}
}

bool AGJDoor::IsConnected(TArray<int> IDs)
{
	bool Connected = false;
	
	for (auto SelfID : ConnectionIDs)
	{
		for (auto LampID : IDs)
		{
			if (SelfID == LampID)
			{
				Connected = true;
				break;
			}
		}
	}

	return Connected;
}

