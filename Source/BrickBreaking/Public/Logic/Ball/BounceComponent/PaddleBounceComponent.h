// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcadeBounceComponent.h"
#include "PaddleBounceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BRICKBREAKING_API UPaddleBounceComponent : public UArcadeBounceComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPaddleBounceComponent();
	
	virtual void BeginPlay() override;
	
	virtual FArcadeBounceResponse GetBounceResponse_Implementation(const FVector& InVelocity, const FHitResult& Hit) override;
	
	float ComputedPaddleHalfWidth = -1.0f;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin = 5.0f, ClampMax = 75.0f))
	float MaxBounceAngle = 65.0f;
};
