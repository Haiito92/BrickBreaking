// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameEvents/UIEventHolder.h"

void UUIEventHolder::LaunchEvent(const EUIEventType& EventType)
{
	switch (EventType)
	{
	case EUIEventType::PlayClicked:
		{
			PlayClicked.Broadcast();
			break;
		}
	case EUIEventType::HomeClicked:
		{
			HomeClicked.Broadcast();
			break;
		}
	case EUIEventType::QuitClicked:
		{
			QuitClicked.Broadcast();
			break;
		}
	}
}
