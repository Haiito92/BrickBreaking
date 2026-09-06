// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrickGameModeBase.h"
#include "BrickGameMode.generated.h"

class ABrickGrid;
class AGameCamera;
/**
 * 
 */
UCLASS()
class BRICKBREAKING_API ABrickGameMode : public ABrickGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual bool InitializeGame_Implementation() override;
	
	virtual void StartGame_Implementation() override;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGameCamera> GameCamera;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickGrid> GridGenerator;
};
