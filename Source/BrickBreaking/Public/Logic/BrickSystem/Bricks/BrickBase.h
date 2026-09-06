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

	UFUNCTION(BlueprintCallable)
	void InitializeBrick();
	
	virtual void Hit_Implementation() override;
	virtual void Break_Implementation() override;

	UFUNCTION(BlueprintCallable)
	int GetScore() const;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBreakedSignature, ABrickBase*, Brick);
	UPROPERTY(BlueprintAssignable)
	FBreakedSignature Breaked;

protected:
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BoxCollision;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, Category="Brick")
	int MaxHealth = 1;
	
	UPROPERTY(VisibleAnywhere, Category="Brick")
	int Health = 1;
	
	UPROPERTY()
	bool bBreaked = false;
	
	UPROPERTY(EditAnywhere, Category="Brick")
	int Score = 10;
	
	
};
