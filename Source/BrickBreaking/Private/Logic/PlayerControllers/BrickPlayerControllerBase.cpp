// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/PlayerControllers/BrickPlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"

void ABrickPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (!IsLocalPlayerController()) return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(Subsystem)) 
	{
		FGameplayTag InputsTag = FGameplayTag::RequestGameplayTag("Inputs");
		ULittleDebugLibrary::AddOnScreenDebugMessage(InputsTag, EDebugMessageType::Error,
			"[ABrickPlayerControllerBase] Can't setup input, invalid input subsystem.", FColor::Red, 3.0f);
		return;	
	}

	for (const UInputMappingContext* Context : InputMappingContexts)
	{
		Subsystem->AddMappingContext(Context, 0);
	}
}
