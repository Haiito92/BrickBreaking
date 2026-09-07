// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameModes/MainMenuGameMode.h"

#include "Logic/PlayerControllers/BrickPlayerControllerBase.h"

void AMainMenuGameMode::StartGame_Implementation()
{
	Super::StartGame_Implementation();
	
	
	FInputModeUIOnly InputModeUIOnly = {};
	PlayerController->SetInputMode(InputModeUIOnly);
	PlayerController->SetShowMouseCursor(true);
}
