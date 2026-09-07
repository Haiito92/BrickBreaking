// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BrickGrid.generated.h"

class UScoreWorldSubsystem;
class ABrickBase;

UCLASS()
class BRICKBREAKING_API ABrickGrid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrickGrid();

	UFUNCTION(BlueprintCallable)
	bool InitializeGrid();
	
	UFUNCTION(BlueprintCallable)
	void CreateGrid();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLastBrickBreakedSignature);
	UPROPERTY(BlueprintAssignable)
	FLastBrickBreakedSignature LastBrickBreaked;
	
protected:
	
	UFUNCTION()
	void OnBrickBreaked(ABrickBase* Brick);
	
	UFUNCTION(BlueprintCallable)
	void DestroyBrick(ABrickBase* Brick);

	UFUNCTION(BlueprintCallable, CallInEditor)
	void DestroyAllBricks();
	
	UPROPERTY(EditAnywhere, Category="Grid|Dimensions", meta=(ClampMin=0.0f))
	int Rows;
	UPROPERTY(EditAnywhere, Category="Grid|Dimensions", meta=(ClampMin=0.0f))
	int Columns;
	
	UPROPERTY(EditAnywhere, Category="Grid|Dimensions", meta=(ClampMin=0.0f))
	float RowPadding = 10.f;
	UPROPERTY(EditAnywhere, Category="Grid|Dimensions", meta=(ClampMin=0.0f))
	float ColumnPadding = 10.f;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<ABrickBase>> Bricks;
	
	UPROPERTY(EditAnywhere, Category="Grid|Bricks")
	TSubclassOf<ABrickBase> BrickClass;
	
	UPROPERTY()
	TObjectPtr<UScoreWorldSubsystem> ScoreSystem;
	
private:
	FGameplayTag BrickTag;
};
