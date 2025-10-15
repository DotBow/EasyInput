// Copyright (C) Dreamer's Tail

#include "EasyInputComponent.h"

#include "EasyInputBindings.h"
#include "GameFramework/Character.h"


UEasyInputComponent::UEasyInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FGameplayTag UEasyInputComponent::GetActiveInputTag() const
{
	return ActiveInputTag;
}

void UEasyInputComponent::SetActiveInputTag(
	const FGameplayTag& InActiveInputTag)
{
	if (!ensureMsgf(InputTags.HasTag(InActiveInputTag),
		TEXT("Unknown input tag!")))
		return;

	ActiveInputTag = InActiveInputTag;
}

void UEasyInputComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!ensureMsgf(Character,
		TEXT("UEasyInputComponent requires ACharacter outer!")))
		return;

	APlayerController* PlayerController = Cast<APlayerController>(
		Character->GetController());

	if (!ensureMsgf(PlayerController,
		TEXT("Player Controller is invalid!")))
		return;

	SetInputBindings(
		PlayerController, InputBindings, Character);
}

void UEasyInputComponent::SetInputBindings(
	const TObjectPtr<APlayerController>& PlayerController,
	UEasyInputBindings* InInputBindings,
	UObject* Object)
{
	if (!InputTags.HasTag(InInputBindings->InputTag))
	{
		UEasyInputBindings::SetupKeyBindings(
			PlayerController, Object, InInputBindings);
		InputTags.AddTag(InInputBindings->InputTag);
	}
}
