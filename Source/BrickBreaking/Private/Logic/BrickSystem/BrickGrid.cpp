// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/BrickSystem/BrickGrid.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Logic/BrickSystem/Bricks/BrickBase.h"
#include "Logic/ScoreSystem/ScoreWorldSubsystem.h"


// Sets default values
ABrickGrid::ABrickGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	BrickTag = FGameplayTag::RequestGameplayTag("BrickSystem");
}

bool ABrickGrid::InitializeGrid()
{
	ScoreSystem = GetWorld()->GetSubsystem<UScoreWorldSubsystem>();
	
	if (!IsValid(ScoreSystem))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(BrickTag, EDebugMessageType::Error,
			"[ABrickGrid] Invalid score system. Failed init.", FColor::Red, 3.0f);
		return false;
	}
	
	Bricks.Empty();
	
	return true;
}

void ABrickGrid::CreateGrid()
{
	FVector Origin = GetActorLocation();

	
	UWorld* World = GetWorld();
	if (!IsValid(BrickClass))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(BrickTag, EDebugMessageType::Error,
			"[ABrickGrid] Invalid brick class. Can't create Grid", FColor::Red, 3.0f);
		return;
	}
	
	for (int i = 0; i < Columns; ++i)
	{
		for (int j = 0; j < Rows; ++j)
		{
			FVector Location = FVector(Origin.X + j * ColumnPadding, Origin.Y + i * RowPadding, Origin.Z);
			FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
			
			ABrickBase* Brick = Cast<ABrickBase>(World->SpawnActor(BrickClass, &Location, &Rotation));	
			
			if (!IsValid(Brick))
			{
				ULittleDebugLibrary::AddOnScreenDebugMessage(BrickTag, EDebugMessageType::Error,
			"[ABrickGridGenerator] Failed to create brick.", FColor::Red, 3.0f);
				continue;
			}
			
			Brick->Breaked.AddDynamic(this, &ABrickGrid::OnBrickBreaked);
			Bricks.Add(Brick);
		}
	}
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(BrickTag, EDebugMessageType::Log,
			"[ABrickGridGenerator] Grid Created. Brick Amount: " + FString::SanitizeFloat(Bricks.Num()), FColor::Magenta, 3.0f);
}

void ABrickGrid::OnBrickBreaked(ABrickBase* Brick)
{
	if (!IsValid(Brick) || !IsValid(ScoreSystem) || !Bricks.Contains(Brick))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(BrickTag, EDebugMessageType::Error,
			"[ABrickGridGenerator] Can't destroy invalid brick.", FColor::Red, 3.0f);

		return;
	}
	
	DestroyBrick(Brick);
}

void ABrickGrid::DestroyBrick(ABrickBase* Brick)
{
	ScoreSystem->AddScore(Brick->GetScore());
	
	Bricks.Remove(Brick);
	
	Brick->Destroy();
	
	ULittleDebugLibrary::AddOnScreenDebugMessage(BrickTag, EDebugMessageType::Log,
	                                             "[ABrickGridGenerator] Brick Destroyed. Brick Amount: " + FString::SanitizeFloat(Bricks.Num()), FColor::Magenta, 3.0f);

	if (Bricks.Num() <= 0)
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(BrickTag, EDebugMessageType::Log,
		                                             "[ABrickGridGenerator] Last Brick Breaked", FColor::Magenta, 3.0f);
		LastBrickBreaked.Broadcast();
	}
}

void ABrickGrid::DestroyAllBricks()
{
	TArray<ABrickBase*> BrickToDestroy = Bricks;
	
	for (ABrickBase* Brick : BrickToDestroy)
	{
		DestroyBrick(Brick);
	}
}

