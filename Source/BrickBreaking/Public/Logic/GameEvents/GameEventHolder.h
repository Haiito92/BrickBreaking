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
	None,
	GameStarted,
	GameEnded,
	PlayerBallShot,
};

USTRUCT(BlueprintType)
struct FGameEventInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameEventType EventType = EGameEventType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EventBool = false;
};

UCLASS(BlueprintType, Blueprintable)
class BRICKBREAKING_API UGameEventHolder : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="EventType"))
	void LaunchEvent(const FGameEventInfo& EventInfo);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameEventSignature, const FGameEventInfo&, GameEventInfo);
	
	UPROPERTY(BlueprintAssignable)
	FGameEventSignature GameStarted;
	UPROPERTY(BlueprintAssignable)
	FGameEventSignature GameEnded;
	UPROPERTY(BlueprintAssignable)
	FGameEventSignature PlayerBallShot;
	
};
