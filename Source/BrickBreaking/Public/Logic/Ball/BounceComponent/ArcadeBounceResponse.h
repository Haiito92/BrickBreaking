// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ArcadeBounceResponse.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBounceType : uint8
{
	Default,
	Custom,
	Sticky
};

USTRUCT(BlueprintType)
struct BRICKBREAKING_API FArcadeBounceResponse
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBounceType BounceType = EBounceType::Default;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CustomDirection = FVector(0.0f, 0.0f, 0.0f);
};
