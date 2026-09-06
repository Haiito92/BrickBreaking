// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameModes/BrickGameMode.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/Camera/GameCamera.h"

bool ABrickGameMode::InitializeGame_Implementation()
{
	if (!Super::InitializeGame_Implementation())
	{
		return false;
	}
	
	FGameplayTag GameLoopTag = FGameplayTag::RequestGameplayTag("GameLoop");
	
	GameCamera = Cast<AGameCamera>(UGameplayStatics::GetActorOfClass(this, AGameCamera::StaticClass()));
	
	if (!IsValid(GameCamera))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Can't init, invalid game camera.", FColor::Red, 3.0f);
		return false;	
	}
	
	return true;
}
