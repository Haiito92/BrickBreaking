// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/GameEvents/GameEventHolder.h"

void UGameEventHolder::LaunchEvent(const FGameEventInfo& EventInfo)
{
	switch (EventInfo.EventType)
	{
	case EGameEventType::GameStarted:
		{
			GameStarted.Broadcast(EventInfo);
			return;
		}
	case EGameEventType::GameEnded:
		{
			GameEnded.Broadcast(EventInfo);
			return;
		}
	case EGameEventType::PauseStateChanged:
		{
			PauseStateChanged.Broadcast(EventInfo);
			return;
		}
	case EGameEventType::PlayerBallShot:
		{
			PlayerBallShot.Broadcast(EventInfo);
			return;
		}
	default:
		{
			return;
		}
	}
}
