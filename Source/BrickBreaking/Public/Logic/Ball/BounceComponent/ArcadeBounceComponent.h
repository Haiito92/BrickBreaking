// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ArcadeBounceComponent.generated.h"

struct FArcadeBounceResponse;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class BRICKBREAKING_API UArcadeBounceComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UArcadeBounceComponent();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FArcadeBounceResponse GetBounceResponse(const FVector& InVelocity, const FHitResult& Hit);
};
