// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Camera/GameCamera.h"

#include "Camera/CameraComponent.h"


// Sets default values
AGameCamera::AGameCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	RootComponent = CameraComponent;
}

