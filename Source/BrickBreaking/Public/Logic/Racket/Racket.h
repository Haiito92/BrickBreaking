// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Racket.generated.h"

class UBoxComponent;
class UFloatingPawnMovement;
class UInputAction;

UCLASS()
class BRICKBREAKING_API ARacket : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARacket();

	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void OnMoveActionTriggered(const FInputActionValue& InputActionValue);
	
	UFUNCTION(BlueprintNativeEvent)
	void DoMove(float InputValue);
	
	UPROPERTY(EditAnywhere, Category="Input|Input Actions")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Racket")
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditAnywhere, Category="Racket")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, Category="Racket")
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
};
