// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
protected:
	UFUNCTION()
	void OnBrickBreaked(ABrickBase* Brick);
	
	UPROPERTY(EditAnywhere, Category="Grid|Dimensions", meta=(ClampMin=0.0f))
	int Rows;
	UPROPERTY(EditAnywhere, Category="Grid|Dimensions", meta=(ClampMin=0.0f))
	int Columns;
	
	UPROPERTY(EditAnywhere, Category="Grid|Dimensions", meta=(ClampMin=0.0f))
	float RowPadding = 10.f;
	UPROPERTY(EditAnywhere, Category="Grid|Dimensions", meta=(ClampMin=0.0f))
	float ColumnPadding = 10.f;
	
	UPROPERTY(EditAnywhere, Category="Grid|Bricks")
	TSubclassOf<ABrickBase> BrickClass;
	
	UPROPERTY()
	TObjectPtr<UScoreWorldSubsystem> ScoreSystem;
};
