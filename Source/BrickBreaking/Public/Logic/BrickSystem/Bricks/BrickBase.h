// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeBrick();
	
	virtual void Hit_Implementation() override;
	virtual void Break_Implementation() override;

	UFUNCTION(BlueprintCallable)
	int GetScore() const;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBreakedSignature, ABrickBase*, Brick);
	UPROPERTY(BlueprintAssignable)
	FBreakedSignature Breaked;

protected:
	
	FGameplayTag BrickTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Brick")
	int MaxHealth = 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Brick")
	int Health = 1;
	
	UPROPERTY(EditAnywhere, Category="Brick")
	TArray<TObjectPtr<UStaticMesh>> BrickMeshes;
	
	UPROPERTY()
	bool bBreaked = false;
	
	UPROPERTY(EditAnywhere, Category="Brick")
	int Score = 10;
	
public:
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	
#endif
};
