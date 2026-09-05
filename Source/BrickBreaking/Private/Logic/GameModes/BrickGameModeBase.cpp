// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameModes/BrickGameModeBase.h"

void ABrickGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeGame();
	InitializeUI();
	
	StartGame();
}

void ABrickGameModeBase::InitializeGame()
{
}

void ABrickGameModeBase::InitializeUI()
{
}

void ABrickGameModeBase::StartGame()
{
}

void ABrickGameModeBase::EndGame()
{
}
