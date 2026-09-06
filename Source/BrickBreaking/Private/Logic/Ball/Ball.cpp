// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Ball/Ball.h"

#include "Components/SphereComponent.h"
#include "Logic/Ball/BounceComponent/ArcadeBounceComponent.h"
#include "Logic/Ball/BounceComponent/ArcadeBounceResponse.h"
#include "Logic/Breakable/Breakable.h"


// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	RootComponent = SphereComponent;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	FVector Forward = GetActorForwardVector();
	Direction.X =  Forward.X;
	Direction.Y =  Forward.Y;
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ComputePhysics(DeltaTime);
}

void ABall::ComputePhysics(float DeltaTime)
{
	FVector Velocity = Direction * Speed; 
	FVector Offset = Velocity * DeltaTime;
	
	FHitResult Hit;
	AddActorWorldOffset(Offset, true, &Hit);
	
	if (!Hit.bBlockingHit) return;
	
	AActor* HitActor = Hit.GetActor();
	
	if (HitActor->Implements<UBreakable>())
	{
		IBreakable::Execute_Hit(HitActor);
	}
	
	FArcadeBounceResponse BounceResponse = {};
	if (UArcadeBounceComponent* BounceComponent = HitActor->FindComponentByClass<UArcadeBounceComponent>())
	{
		BounceResponse = BounceComponent->GetBounceResponse(Velocity, Hit);
	}
	
	ApplyBounceResponse(BounceResponse, Hit);
	return;
}

void ABall::ApplyBounceResponse(const FArcadeBounceResponse& Response, const FHitResult& Hit)
{
	switch (Response.BounceType)
	{
	case EBounceType::Default:
		{
			Direction = Direction.MirrorByVector(Hit.Normal);
			Direction.Z = 0.0f;
			Direction.Normalize();
			return;
		}
	case EBounceType::Custom:
		{
			Direction = Response.CustomDirection;
			return;
		}
	case EBounceType::Sticky:
		{
			return;
		}
	}
}

