// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/PlayerControllers/BrickPlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"

void ABrickPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (!IsLocalPlayerController()) return;
	FGameplayTag InputsTag = FGameplayTag::RequestGameplayTag("Inputs");
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(Subsystem)) 
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(InputsTag, EDebugMessageType::Error,
			"[ABrickPlayerControllerBase] Can't setup input, invalid input subsystem.", FColor::Red, 3.0f);
		return;	
	}

	for (const UInputMappingContext* Context : InputMappingContexts)
	{
		Subsystem->AddMappingContext(Context, 0);
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(InputsTag, EDebugMessageType::Error,
			"[ABrickPlayerControllerBase] Can't bind input actions, invalid input component.", FColor::Red, 3.0f);
		return;
	}
	
	if (IsValid(PauseAction))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ABrickPlayerControllerBase::OnPauseActionStarted);
	}
	else
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(InputsTag, EDebugMessageType::Error,
			"[ABrickPlayerControllerBase] Invalid pause action, can't bind.", FColor::Red, 3.0f);
	}
}

void ABrickPlayerControllerBase::OnPauseActionStarted_Implementation(const FInputActionValue& InputActionValue)
{
	SetPause(!IsPaused());
}
