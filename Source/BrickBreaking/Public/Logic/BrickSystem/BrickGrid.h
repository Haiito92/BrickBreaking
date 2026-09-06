// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrickGrid.generated.h"

class ABrickBase;

UCLASS()
class BRICKBREAKING_API ABrickGrid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrickGrid();
		
	UFUNCTION(BlueprintCallable)
	void CreateGrid();
	
protected:
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
};
