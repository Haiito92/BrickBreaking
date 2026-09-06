// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/BrickSystem/Bricks/BrickBase.h"

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
}

void ABrickBase::Hit_Implementation()
{
	IBreakable::Hit_Implementation();
	
	Health = FMath::Max(Health - 1, 0);
	
	if (Health <= 0 && !bBreaked)
	{
		IBreakable::Execute_Break(this);
	}
}

void ABrickBase::Break_Implementation()
{
	IBreakable::Break_Implementation();
	
	Breaked.Broadcast();
	
	Destroy();
}

