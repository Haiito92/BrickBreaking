// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/ShakeSystem/ShakeWorldSubsystem.h"
#include "EngineUtils.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Logic/ShakeSystem/ShakeableComponent.h"

void UShakeWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

TStatId UShakeWorldSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UShakeWorldSubsystem, STATGROUP_Tickables);
}

bool UShakeWorldSubsystem::InitializeShakeSystem()
{
	ShakeTag = FGameplayTag::RequestGameplayTag("ShakeSystem");
	
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
	ULittleDebugLibrary::LogAndAddOnScreenDebugMessage(ShakeTag, EDebugMessageType::Log,
		"[UShakeWorldSubsystem] Launch Shake. Nb Shakeables: " + Shakeables.Num(), FColor::Orange, 3.0f);
	
	for (UShakeableComponent* Shakeable : Shakeables)
	{
		IShakeable::Execute_Shake(Shakeable, ShakeStrength);
	}
}
