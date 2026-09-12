// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Audio/AudioGameInstanceSubsystem.h"

#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UAudioGameInstanceSubsystem::InitializeAudioSystem()
{
	AudioTag = FGameplayTag::RequestGameplayTag("AudioSystem");
	
	ULittleDebugLibrary::LogAndAddOnScreenDebugMessage(AudioTag, EDebugMessageType::Log, 
		"[UAudioGameInstanceSubsystem] Init Audio System.", FColor::Turquoise, 3.0f);
}

void UAudioGameInstanceSubsystem::SwitchMusic(USoundBase* NewMusic, float FadeDuration)
{
	if (IsValid(MusicComponent) && MusicComponent->Sound == NewMusic && MusicComponent->IsPlaying())
	{
		ULittleDebugLibrary::LogAndAddOnScreenDebugMessage(AudioTag, EDebugMessageType::Log, 
		"[UAudioGameInstanceSubsystem] Music already playing.", FColor::Turquoise, 3.0f);
		return;
	}
	
	UAudioComponent* OldComponent = MusicComponent;
	
	if (!IsValid(OldComponent))
	{
		UAudioComponent* NewComponent = UGameplayStatics::SpawnSound2D(GetWorld(), 
		NewMusic,
		1.0f,
		1.0,
		0.0f,
		nullptr,
		true,
		false
		);
	
		MusicComponent = NewComponent;
		NewComponent->Play();
		NewComponent->FadeIn(FadeDuration, 1.0f);
		return;
	}
	
	OldComponent->FadeOut(FadeDuration, 0.0f);
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [OldComponent, FadeDuration, NewMusic, this]()
	{
		if (IsValid(OldComponent))
		{
			OldComponent->Stop();
			OldComponent->DestroyComponent();
		}	
		
		if (IsValid(this))
		{
			UAudioComponent* NewComponent = UGameplayStatics::SpawnSound2D(GetWorld(), 
				NewMusic,
				1.0f,
				1.0,
				0.0f,
				nullptr,
				true,
				false
			);
	
			MusicComponent = NewComponent;
			NewComponent->Play();
			NewComponent->FadeIn(FadeDuration, 1.0f);
		}
		
	}, FadeDuration + 0.1f, false);
}
