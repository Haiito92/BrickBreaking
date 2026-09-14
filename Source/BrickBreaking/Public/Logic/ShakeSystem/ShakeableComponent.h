// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shakeable.h"
#include "Components/ActorComponent.h"
#include "ShakeableComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BRICKBREAKING_API UShakeableComponent : public UActorComponent, public IShakeable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UShakeableComponent();

};
