// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/BrickSystem/BrickGrid.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/BrickSystem/Bricks/BrickBase.h"


// Sets default values
ABrickGrid::ABrickGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABrickGrid::CreateGrid()
{
	FVector Origin = GetActorLocation();

	FGameplayTag BrickTag = FGameplayTag::RequestGameplayTag("BrickSystem");
	
	UWorld* World = GetWorld();
	if (!IsValid(BrickClass))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(BrickTag, EDebugMessageType::Error,
			"[ABrickGridGenerator] Invalid brick class. Can't create Grid", FColor::Red, 3.0f);
		return;
	}
	
	for (int i = 0; i < Columns; ++i)
	{
		for (int j = 0; j < Rows; ++j)
		{
			FVector Location = FVector(Origin.X + j * ColumnPadding, Origin.Y + i * RowPadding, Origin.Z);
			FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
			
			World->SpawnActor(BrickClass, &Location, &Rotation);		
		}
	}
}

