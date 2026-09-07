// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

struct FArcadeBounceResponse;
class USphereComponent;

UCLASS()
class BRICKBREAKING_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetDirection(const FVector& InDirection);
	
	UFUNCTION(BlueprintCallable)
	void DestroyBall();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDestroyedSignature, ABall*, Ball);
	UPROPERTY(BlueprintAssignable)
	FDestroyedSignature Destroyed;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Ball")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditAnywhere, Category = "Ball")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball")
	float Speed;
	
	UPROPERTY(BlueprintReadWrite)
	FVector Direction = FVector(0.0f, 0.0f, 0.0f);
	
private:
	void ComputePhysics(float DeltaTime);
	void ApplyBounceResponse(const FArcadeBounceResponse& Response, const FHitResult& Hit);
};
