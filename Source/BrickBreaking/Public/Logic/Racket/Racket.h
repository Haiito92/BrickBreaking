// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Racket.generated.h"

class UGameEventHolder;
class ABall;
class USphereComponent;
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

	UFUNCTION(BlueprintCallable)
	void InitRacket(UGameEventHolder* InGameEventHolder);
	
	UFUNCTION(BlueprintCallable)
	void SpawnBall();
	
	UFUNCTION(BlueprintCallable)
	void ResetMovement();

	UFUNCTION(BlueprintCallable)
	void SetCanMove(bool InCanMove);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLastBallDestroyedSignature);
	UPROPERTY(BlueprintAssignable)
	FLastBallDestroyedSignature LastBallDestroyed;
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void OnMoveActionTriggered(const FInputActionValue& InputActionValue);
	void OnShootActionStarted(const FInputActionValue& InputActionValue);
	
	UFUNCTION(BlueprintNativeEvent)
	void DoMove(float InputValue);
	
	UFUNCTION(BlueprintNativeEvent)
	void DoShoot();
	
	UFUNCTION()
	void OnBallDestroyed(ABall* DestroyedBall);
	
	FGameplayTag InputsTag;
	FGameplayTag PlayerTag;
	
	UPROPERTY(EditAnywhere, Category="Input|Input Actions")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input|Input Actions")
	TObjectPtr<UInputAction> ShootAction;
	
	UPROPERTY(EditAnywhere, Category="Racket")
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditAnywhere, Category="Racket")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, Category="Racket")
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
	
	UPROPERTY(EditAnywhere, Category="Racket")
	TObjectPtr<USphereComponent> ShootingPoint;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGameEventHolder> GameEventHolder;
	
	UPROPERTY(BlueprintReadWrite)
	bool bCanMove;
	
	UPROPERTY(EditAnywhere, Category="Racket|Ball")
	TSubclassOf<ABall> BallClass;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABall> Ball;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsBallAttached;
};
