// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Racket/Racket.h"

#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Logic/Ball/Ball.h"


// Sets default values
ARacket::ARacket()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	InputsTag = FGameplayTag::RequestGameplayTag("Inputs");
	PlayerTag = FGameplayTag::RequestGameplayTag("Inputs");
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxComponent;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	FloatingPawnMovement->UpdatedComponent = RootComponent;
	
	ShootingPoint = CreateDefaultSubobject<USphereComponent>("ShootingPoint");
	ShootingPoint->SetupAttachment(Mesh);
	
	FCollisionResponseContainer ResponseContainer = {};
	ResponseContainer.SetAllChannels(ECR_Ignore);
	ShootingPoint->SetCollisionResponseToChannels(ResponseContainer);
	
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

void ARacket::InitRacket()
{
	
}

void ARacket::SpawnBall()
{
	if (!IsValid(BallClass))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(PlayerTag, EDebugMessageType::Error,
			"[ARacket] Failed to spawn ball, invalid ball class.", FColor::Red, 3.0f);
		return;
	}
	
	FVector SpawnLocation = ShootingPoint->GetComponentLocation();
	FRotator SpawnRotation = ShootingPoint->GetComponentRotation();
	Ball = Cast<ABall>(GetWorld()->SpawnActor(BallClass, &SpawnLocation, &SpawnRotation));
	
	if (!IsValid(Ball))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(PlayerTag, EDebugMessageType::Error,
			"[ARacket] Failed to spawn ball correctly.", FColor::Red, 3.0f);
		return;
	}
	
	Ball->Destroyed.AddDynamic(this, &ARacket::OnBallDestroyed);
	IsBallAttached = true;
	
	FAttachmentTransformRules AttachmentRules = {EAttachmentRule::KeepWorld, false};
	Ball->AttachToComponent(ShootingPoint, AttachmentRules);
}

void ARacket::ResetMovement()
{
	FloatingPawnMovement->Velocity = FVector(0.0f, 0.0f, 0.0f);
	ConsumeMovementInputVector();
}

void ARacket::SetCanMove(bool InCanMove)
{
	bCanMove = InCanMove;
}

// Called to bind functionality to input
void ARacket::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
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
	
	if (IsValid(ShootAction))
	{
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ARacket::OnShootActionStarted);
	}
	else
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(InputsTag, EDebugMessageType::Error,
			"[ARacket] Shoot action invalid, can't bind.", FColor::Red, 3.0f);
	}
}

void ARacket::OnMoveActionTriggered(const FInputActionValue& InputActionValue)
{
	float InputValue = InputActionValue.Get<float>();
	
	DoMove(InputValue);
}

void ARacket::OnShootActionStarted(const FInputActionValue& InputActionValue)
{
	ULittleDebugLibrary::AddOnScreenDebugMessage(InputsTag, EDebugMessageType::Log,
			"[ARacket] Shoot action started.", FColor::Cyan, 3.0f);
	DoShoot();
}

void ARacket::OnBallDestroyed(ABall* DestroyedBall)
{
	if (DestroyedBall != Ball) return;
	
	Ball->Destroyed.RemoveDynamic(this, &ARacket::OnBallDestroyed);
	Ball = nullptr;
	IsBallAttached = false;
	
	LastBallDestroyed.Broadcast();
}

void ARacket::DoShoot_Implementation()
{
	if (!IsBallAttached) return;

	IsBallAttached = false;
	FDetachmentTransformRules DetachmentRules = {EDetachmentRule::KeepWorld, false};
	Ball->DetachFromActor(DetachmentRules);
	
	Ball->SetDirection(GetActorForwardVector());
}

void ARacket::DoMove_Implementation(float InputValue)
{
	if (!bCanMove) return;
	
	AddMovementInput(GetActorRightVector(), InputValue);	
}

