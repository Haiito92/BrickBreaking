// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/ScoreSystem/ScoreWorldSubsystem.h"

bool UScoreWorldSubsystem::InitializeScoreSystem()
{
	TotalScore = 0;
	
	return true;
}

void UScoreWorldSubsystem::AddScore(int ScoreAdded)
{
	TotalScore += ScoreAdded;
}

void UScoreWorldSubsystem::RemoveScore(int ScoreRemoved)
{
	TotalScore -= ScoreRemoved;
}

int UScoreWorldSubsystem::GetTotalScore() const
{
	return TotalScore;
}
