// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/ShakeSystem/ShakeWorldSubsystem.h"
#include "EngineUtils.h"
#include "Logic/ShakeSystem/ShakeableComponent.h"

bool UShakeWorldSubsystem::InitializeShakeSystem()
{
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (UShakeableComponent* ShakeableComponent = Actor->FindComponentByClass<UShakeableComponent>())
		{
			Shakeables.Add(ShakeableComponent);
		}
	}
	
	return true;
}

void UShakeWorldSubsystem::LaunchShake(float ShakeStrength)
{
	for (UShakeableComponent* Shakeable : Shakeables)
	{
		IShakeable::Execute_Shake(Shakeable, ShakeStrength);
	}
}
