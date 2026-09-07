// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameModes/BrickGameMode.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/BrickSystem/BrickGrid.h"
#include "Logic/Camera/GameCamera.h"
#include "Logic/GameEvents/GameEventHolder.h"
#include "Logic/PlayerControllers/BrickPlayerControllerBase.h"
#include "Logic/Racket/Racket.h"
#include "Logic/ScoreSystem/ScoreWorldSubsystem.h"

bool ABrickGameMode::InitializeGame_Implementation()
{
	if (!Super::InitializeGame_Implementation())
	{
		return false;
	}
	
	GameCamera = Cast<AGameCamera>(UGameplayStatics::GetActorOfClass(this, AGameCamera::StaticClass()));
	
	if (!IsValid(GameCamera))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Can't init, invalid game camera.", FColor::Red, 3.0f);
		return false;	
	}
	
	GridGenerator = Cast<ABrickGrid>(UGameplayStatics::GetActorOfClass(this, ABrickGrid::StaticClass()));
	
	if (!IsValid(GridGenerator))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Can't init, invalid GridGenerator.", FColor::Red, 3.0f);
		return false;	
	}
	
	
	UScoreWorldSubsystem* ScoreSystem = GetWorld()->GetSubsystem<UScoreWorldSubsystem>();
	if (!IsValid(ScoreSystem))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Failed init, invalid Score system.", FColor::Red, 3.0f);
		return false;
	}
	
	if (!ScoreSystem->InitializeScoreSystem())
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Failed init, failed init Score system.", FColor::Red, 3.0f);
		return false;
	}
	
	GridGenerator->InitializeGrid();
	GridGenerator->CreateGrid();
		
	PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(this, APlayerStart::StaticClass()));
	if (!IsValid(PlayerStart))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Failed init, can't find player start.", FColor::Red, 3.0f);
		return false;
	}
	
	if (!IsValid(PlayerClass))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Failed init, player class invalid.", FColor::Red, 3.0f);
		return false;
	}
	
	FVector SpawnLocation = PlayerStart->GetActorLocation();
	FRotator SpawnRotation = PlayerStart->GetActorRotation();
	PlayerRacket = Cast<ARacket>(GetWorld()->SpawnActor(PlayerClass, &SpawnLocation, &SpawnRotation));
	if (!IsValid(PlayerRacket))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Failed init, failed to create valid player racket.", FColor::Red, 3.0f);
		return false;
	}
	
	PlayerRacket->InitRacket();
	PlayerRacket->LastBallDestroyed.AddDynamic(this, &ABrickGameMode::OnLastPlayerBallDestroyed);
	PlayerController->Possess(PlayerRacket);
	
	PlayerRacket->SpawnBall();
	
	
	return true;
}

void ABrickGameMode::StartGame_Implementation()
{
	Super::StartGame_Implementation();
	
	FInputModeUIOnly InputModeUIOnly = {};
	PlayerController->SetInputMode(InputModeUIOnly);
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] Start Game.", FColor::Emerald, 3.0f);

	GameEventHolder->LaunchEvent({EGameEventType::GameStarted});
	
	FInputModeGameOnly InputModeGameOnly = {};
	PlayerController->SetInputMode(InputModeGameOnly);
	PlayerRacket->SetCanMove(true);
}

void ABrickGameMode::EndGame_Implementation(bool Won)
{
	Super::EndGame_Implementation(Won);
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameMode] End Game, victory: " + LexToString(Won), FColor::Emerald, 3.0f);
	
	PlayerRacket->SetCanMove(false);
	PlayerRacket->ResetMovement();
	
	FInputModeUIOnly InputModeUIOnly = {};
	PlayerController->SetInputMode(InputModeUIOnly);
	PlayerController->SetShowMouseCursor(true);
	
	GameEventHolder->LaunchEvent({EGameEventType::GameEnded, Won});
}

void ABrickGameMode::OnLastPlayerBallDestroyed()
{
	EndGame(false);
}
