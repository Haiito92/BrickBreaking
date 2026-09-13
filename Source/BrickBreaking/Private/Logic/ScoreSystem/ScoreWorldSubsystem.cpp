// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/ScoreSystem/ScoreWorldSubsystem.h"

#include "LittleDebugLibrary.h"
#include "MessageType.h"

bool UScoreWorldSubsystem::InitializeScoreSystem()
{
	TotalScore = 0;
	
	ScoreTag = FGameplayTag::RequestGameplayTag("ScoreSystem");
	
	return true;
}

void UScoreWorldSubsystem::AddScore(int ScoreAdded)
{
	int OldScore = TotalScore;
	
	TotalScore += Combo > 1 ? ScoreAdded * Combo : ScoreAdded;
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(ScoreTag, EDebugMessageType::Log,
		"[UScoreWorldSubsystem] New Score: " + FString::SanitizeFloat(TotalScore), FColor::Emerald, 3.0f);
	
	ScoreUpdated.Broadcast(OldScore, TotalScore);
}

void UScoreWorldSubsystem::RemoveScore(int ScoreRemoved)
{
	int OldScore = TotalScore;
	TotalScore -= ScoreRemoved;
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(ScoreTag, EDebugMessageType::Log,
		"[UScoreWorldSubsystem] New Score: " + FString::SanitizeFloat(TotalScore), FColor::Emerald, 3.0f);
	
	ScoreUpdated.Broadcast(OldScore, TotalScore);
}

int UScoreWorldSubsystem::GetTotalScore() const
{
	return TotalScore;
}

void UScoreWorldSubsystem::IncrementCombo()
{
	if (Combo == 0) ComboStarted.Broadcast();
	
	Combo++;
	
	ComboIncremented.Broadcast(Combo);
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(ScoreTag, EDebugMessageType::Log,
		"[UScoreWorldSubsystem] New Combo: " + FString::SanitizeFloat(Combo), FColor::Emerald, 3.0f);
}

void UScoreWorldSubsystem::ResetCombo()
{
	Combo = 0;
	
	ComboReset.Broadcast();
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(ScoreTag, EDebugMessageType::Log,
		"[UScoreWorldSubsystem] Combo Reset", FColor::Emerald, 3.0f);
}
