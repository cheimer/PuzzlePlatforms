// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{

}

void UPuzzlePlatformsGameInstance::Init()
{

}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if(!Engine) return;
	Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Hosting"));

	if(!GetWorld()) return;

	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Red, FString::Printf(TEXT("Join %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!PlayerController) return;

	PlayerController->ClientTravel(Address, TRAVEL_Absolute);
}
