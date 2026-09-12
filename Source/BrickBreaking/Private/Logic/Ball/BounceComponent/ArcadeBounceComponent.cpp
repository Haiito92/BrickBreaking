// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Ball/BounceComponent/ArcadeBounceComponent.h"
#include "Logic/Ball/BounceComponent/ArcadeBounceResponse.h"

UArcadeBounceComponent::UArcadeBounceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UArcadeBounceComponent::ReactToBounce_Implementation()
{
	ReceiveReactToBounce();
}

FArcadeBounceResponse UArcadeBounceComponent::GetBounceResponse_Implementation(const FVector& InVelocity, const FHitResult& Hit)
{
	return {};
}
