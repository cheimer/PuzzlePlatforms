// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(HasAuthority() && ActiveTriggers > 0)
	{
		FVector Location = GetActorLocation();
		float TotalLength = (GlobalTargetLocation - GlobalStartLocation).Length();
		float CurrentLength = (Location - GlobalStartLocation).Length();
		if(TotalLength <= CurrentLength)
		{
			Swap(GlobalStartLocation, GlobalTargetLocation);
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += MoveSpeed * DeltaSeconds * Direction;
		SetActorLocation(Location);
	}

}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if(ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}
