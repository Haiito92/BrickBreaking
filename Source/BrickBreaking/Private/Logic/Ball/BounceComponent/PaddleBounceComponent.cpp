// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Ball/BounceComponent/PaddleBounceComponent.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Logic/Ball/BounceComponent/ArcadeBounceResponse.h"


// Sets default values for this component's properties
UPaddleBounceComponent::UPaddleBounceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPaddleBounceComponent::BeginPlay()
{
	Super::BeginPlay();
	FGameplayTag BallSystemTag = FGameplayTag::RequestGameplayTag("BallSystem");
	
	UPrimitiveComponent* OwnerCollisionComp = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if (!IsValid(OwnerCollisionComp))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(BallSystemTag, EDebugMessageType::Error,
			"[UPaddleBounceComponent] Failed to compute half width", FColor::Red, 3.0f);
		return;
	}
	
	FBoxSphereBounds Bounds = OwnerCollisionComp->CalcBounds(FTransform::Identity);
	ComputedPaddleHalfWidth = Bounds.BoxExtent.Y * 0.5f;
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(BallSystemTag, EDebugMessageType::Log,
			"[UPaddleBounceComponent] Half width:" + FString::SanitizeFloat(ComputedPaddleHalfWidth), FColor::White, 3.0f);
}

FArcadeBounceResponse UPaddleBounceComponent::GetBounceResponse_Implementation(const FVector& InVelocity,
                                                                               const FHitResult& Hit)
{
	if (ComputedPaddleHalfWidth <= 0) return {};
	
	AActor* Paddle = GetOwner();
	
	FVector LocalHit = Hit.ImpactPoint - Paddle->GetActorLocation();
	float RawOffset = FVector::DotProduct(LocalHit, Paddle->GetActorRightVector());
	float NormalizedOffset = FMath::Clamp(RawOffset / ComputedPaddleHalfWidth, -1.0f, 1.0f);
	
	float BounceAngle = NormalizedOffset * MaxBounceAngle;
	
	FVector BounceDir = Paddle->GetActorForwardVector().RotateAngleAxis(BounceAngle, Paddle->GetActorUpVector());
	BounceDir.Z = 0.0f;
	BounceDir.Normalize();
	
	FArcadeBounceResponse BounceResponse = {};
	BounceResponse.BounceType = EBounceType::Custom;
	BounceResponse.CustomDirection = BounceDir;
	
	return BounceResponse;
}

