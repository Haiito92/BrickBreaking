// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Racket/Racket.h"

#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ARacket::ARacket()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxComponent;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	FloatingPawnMovement->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ARacket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARacket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARacket::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	FGameplayTag InputsTag = FGameplayTag::RequestGameplayTag("Inputs");
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		
		ULittleDebugLibrary::AddOnScreenDebugMessage(InputsTag, EDebugMessageType::Error,
			"[ARacket] Can't bind actions, invalid input component.", FColor::Red, 3.0f);
		return;
	}

	if (IsValid(MoveAction))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARacket::OnMoveActionTriggered);
	}
	else
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(InputsTag, EDebugMessageType::Error,
			"[ARacket] Move action invalid, can't bind.", FColor::Red, 3.0f);
	}
}

void ARacket::OnMoveActionTriggered(const FInputActionValue& InputActionValue)
{
	float InputValue = InputActionValue.Get<float>();
	
	DoMove(InputValue);
}

void ARacket::DoMove_Implementation(float InputValue)
{
	AddMovementInput(GetActorRightVector(), InputValue);	
}

