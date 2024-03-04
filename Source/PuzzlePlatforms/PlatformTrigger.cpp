// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"

#include "MovingPlatform.h"
#include "Components/BoxComponent.h"

APlatformTrigger::APlatformTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	SetRootComponent(TriggerVolume);

}

void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	if(TriggerVolume)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerEnd);

	}
	
}

void APlatformTrigger::OnTriggerBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for(AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnTriggerEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for(AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}

void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

