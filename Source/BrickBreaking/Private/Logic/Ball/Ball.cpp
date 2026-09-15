// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Ball/Ball.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
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

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ComputePhysics(DeltaTime);
}

void ABall::SetDirection(const FVector& InDirection)
{
	Direction = InDirection;
}

void ABall::DestroyBall()
{
	Destroyed.Broadcast(this);
	Destroy();
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
	
	ReceiveBallBounce(Hit);
	
	FArcadeBounceResponse BounceResponse = {};
	if (UArcadeBounceComponent* BounceComponent = HitActor->FindComponentByClass<UArcadeBounceComponent>())
	{
		BounceComponent->ReactToBounce();
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
			break;
		}
	case EBounceType::Custom:
		{
			Direction = Response.CustomDirection;
			break;
		}
	case EBounceType::Sticky:
		{
			return;
		}
	}
	
	if (FMath::IsNearlyEqual(Direction.X, 0.0f)) return;
	
	const float MinHorizontalAngle = 15.0f;
	const float MinHorizontalAngleRad = FMath::DegreesToRadians(MinHorizontalAngle);
	float CurrentAngle = FMath::RadiansToDegrees(FMath::Asin(FMath::Abs(Direction.X)));
	
	if (CurrentAngle < MinHorizontalAngle)
	{
		float XSign = FMath::Sign(Direction.X) == 0.0f ? 1.0f : FMath::Sign(Direction.X);
		float YSign = FMath::Sign(Direction.Y) == 0.0f ? 1.0f : FMath::Sign(Direction.Y);
		
		Direction.X = XSign * FMath::Sin(MinHorizontalAngleRad);
		Direction.Y = YSign * FMath::Cos(MinHorizontalAngleRad);
		
		Direction.Normalize();
	}
}

