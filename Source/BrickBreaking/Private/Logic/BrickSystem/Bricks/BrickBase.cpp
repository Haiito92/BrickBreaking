// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/BrickSystem/Bricks/BrickBase.h"

#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Components/BoxComponent.h"


// Sets default values
ABrickBase::ABrickBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	BrickTag = FGameplayTag::RequestGameplayTag("BrickSystem");
}

void ABrickBase::InitializeBrick_Implementation()
{
	Health = MaxHealth;
}

void ABrickBase::Hit_Implementation()
{
	IBreakable::Hit_Implementation();
	
	Health = FMath::Max(Health - 1, 0);
	
	if (Health > 0 && Health < BrickMeshes.Num())
	{
		Mesh->SetStaticMesh(BrickMeshes[Health-1]);
		//ULittleDebugLibrary::LogAndAddOnScreenDebugMessage(BrickTag, EDebugMessageType::Log,
		//	"[ABrickBase] Changed mesh to: " + BrickMeshes[Health-1].GetName(), FColor::Orange, 3.0f);
	}
	
	Execute_ReceiveBreakableHit(this);
	
	if (Health <= 0 && !bBreaked)
	{
		IBreakable::Execute_Break(this);
	}
}

void ABrickBase::Break_Implementation()
{
	IBreakable::Break_Implementation();
	
	Execute_ReceiveBreak(this);
	bBreaked = true;
	Breaked.Broadcast(this);
}

int ABrickBase::GetScore() const
{
	return Score;
}



#if WITH_EDITOR
void ABrickBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property == nullptr) return;
	
	FName PropertyName = PropertyChangedEvent.Property->GetFName();
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ABrickBase, MaxHealth))
	{
		BrickMeshes.SetNum(MaxHealth);
	}
}

#endif