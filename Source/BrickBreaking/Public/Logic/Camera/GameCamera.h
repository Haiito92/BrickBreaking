// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"

class UCameraComponent;

UCLASS()
class BRICKBREAKING_API AGameCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameCamera();

	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
};
