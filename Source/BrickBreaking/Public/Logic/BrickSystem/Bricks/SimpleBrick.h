// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrickBase.h"
#include "SimpleBrick.generated.h"

UCLASS()
class BRICKBREAKING_API ASimpleBrick : public ABrickBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimpleBrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
