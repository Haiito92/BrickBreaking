// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "ScoreWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKING_API UScoreWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool InitializeScoreSystem();
	
	UFUNCTION(BlueprintCallable)
	void AddScore(int ScoreAdded);
	
	UFUNCTION(BlueprintCallable)
	void RemoveScore(int ScoreRemoved);
	
	UFUNCTION(BlueprintCallable)
	int GetTotalScore() const;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScoreUpdatedSignature, int, OldScore, int, NewScore);
	UPROPERTY(BlueprintAssignable)
	FScoreUpdatedSignature ScoreUpdated;
	
private:
	int TotalScore;
	
	FGameplayTag ScoreTag;
};
