// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameEventHolder.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameEventType : uint8
{
	GameStarted,
	GameEnded,
	PlayerBallShot,
};

UCLASS()
class BRICKBREAKING_API UGameEventHolder : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="EventType"))
	void LaunchEvent(const EGameEventType& EventType);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimpleGameEventSignature);
	
	UPROPERTY(BlueprintAssignable)
	FSimpleGameEventSignature GameStarted;
	UPROPERTY(BlueprintAssignable)
	FSimpleGameEventSignature GameEnded;
	UPROPERTY(BlueprintAssignable)
	FSimpleGameEventSignature PlayerBallShot;
	
};
