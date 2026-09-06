// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logic/Breakable/Breakable.h"
#include "BrickBase.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class BRICKBREAKING_API ABrickBase : public AActor, public IBreakable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrickBase();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BoxCollision;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
