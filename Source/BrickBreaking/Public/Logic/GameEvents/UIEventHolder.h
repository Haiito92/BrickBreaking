// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UIEventHolder.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EUIEventType : uint8
{
	PlayClicked,
	HomeClicked,
	QuitClicked,
};

UCLASS(BlueprintType, Blueprintable)
class BRICKBREAKING_API UUIEventHolder : public UObject
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="EventType"))
	void LaunchEvent(const EUIEventType& EventType);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonClickedSignature);
	
	UPROPERTY(BlueprintAssignable)
	FButtonClickedSignature PlayClicked;
	UPROPERTY(BlueprintAssignable)
	FButtonClickedSignature HomeClicked;
	UPROPERTY(BlueprintAssignable)
	FButtonClickedSignature QuitClicked;
};
