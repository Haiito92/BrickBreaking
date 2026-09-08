// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShaderCompiler.h"
#include "UObject/Object.h"
#include "UIEventHolder.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EUIEventType : uint8
{
	None,
	PlayClicked,
	HomeClicked,
	PauseClicked,
	QuitClicked,
};

USTRUCT(BlueprintType)
struct BRICKBREAKING_API FUIEventInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUIEventType EventType = EUIEventType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EventBool = false;
};

UCLASS(BlueprintType, Blueprintable)
class BRICKBREAKING_API UUIEventHolder : public UObject
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="EventInfo"))
	void LaunchEvent(const FUIEventInfo& EventInfo);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonClickedSignature, const FUIEventInfo&, EventInfo);
	
	UPROPERTY(BlueprintAssignable)
	FButtonClickedSignature PlayClicked;
	UPROPERTY(BlueprintAssignable)
	FButtonClickedSignature HomeClicked;
	UPROPERTY(BlueprintAssignable)
	FButtonClickedSignature PauseClicked;
	UPROPERTY(BlueprintAssignable)
	FButtonClickedSignature QuitClicked;
};
