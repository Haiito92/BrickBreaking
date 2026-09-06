// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrickGameModeBase.h"
#include "BrickGameMode.generated.h"

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
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGameCamera> GameCamera;
};
