// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameEvents/UIEventHolder.h"

void UUIEventHolder::LaunchEvent(const FUIEventInfo& EventInfo)
{
	switch (EventInfo.EventType)
	{
	case EUIEventType::PlayClicked:
		{
			PlayClicked.Broadcast(EventInfo);
			break;
		}
	case EUIEventType::HomeClicked:
		{
			HomeClicked.Broadcast(EventInfo);
			break;
		}
	case EUIEventType::PauseClicked:
		{
			PauseClicked.Broadcast(EventInfo);
			break;
		}
	case EUIEventType::QuitClicked:
		{
			QuitClicked.Broadcast(EventInfo);
			break;
		}
	default:
		{
			return;
		}
	}
}
