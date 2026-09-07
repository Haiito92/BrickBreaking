// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrickGameModeBase.h"
#include "BrickGameMode.generated.h"

class ARacket;
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
	virtual void EndGame_Implementation(bool Won) override;
protected:
	UFUNCTION()
	void OnLastPlayerBallDestroyed();
	UFUNCTION()
	void OnLastBrickBreaked();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGameCamera> GameCamera;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickGrid> BrickGrid;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerStart> PlayerStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ARacket> PlayerClass;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ARacket> PlayerRacket;
};
