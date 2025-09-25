// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#include "EasyInputSubsystem.h"

#include "EasyInputBindings.h"


UE_DEFINE_GAMEPLAY_TAG(Input_Default, "Input.Default")


void UEasyInputSubsystem::Initialize(
	FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	EasyInputSubsystem = this;
	ActiveInputTag = Input_Default;
}

void UEasyInputSubsystem::SetInputBindings(
	const TObjectPtr<APlayerController>& PlayerController,
	UEasyInputBindings* InputBindings,
	UObject* Object)
{
	if (!InputTags.HasTag(InputBindings->InputTag))
	{
		UEasyInputBindings::SetupKeyBindings(
			PlayerController, Object, InputBindings);
		InputTags.AddTag(InputBindings->InputTag);
	}
}

FGameplayTag UEasyInputSubsystem::GetActiveInputTag() const
{
	return ActiveInputTag;
}

void UEasyInputSubsystem::SetActiveInputTag(
	const FGameplayTag& InActiveInputTag)
{
	if (!ensureMsgf(InputTags.HasTag(InActiveInputTag),
		TEXT("Unknown input tag!")))
		return;

	ActiveInputTag = InActiveInputTag;
}


UEasyInputSubsystem* EasyInputSubsystem;
