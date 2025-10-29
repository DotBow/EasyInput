// Copyright (C) Dreamer's Tail

#include "EasyInputComponent.h"

#include "EasyInputBindings.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"


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

	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());

	if (!ensureMsgf(PlayerController,
		TEXT("UEasyInputComponent requires Player Controller outer!")))
		return;

	ACharacter* Character = Cast<ACharacter>(
		PlayerController->GetPawn());

	if (!ensureMsgf(Character,
		TEXT("Character is invalid")))
		return;

	if (!ensureMsgf(InputBindings,
		TEXT("Input Bindings are invalid!")))
		return;

	SetInputBindings(
		PlayerController, Character);
}

void UEasyInputComponent::SetInputBindings(
	const TObjectPtr<APlayerController>& PlayerController,
	const TObjectPtr<ACharacter>& Character)
{
	if (!InputTags.HasTag(InputBindings->InputTag))
	{
		for (const FEasyInputActionBinding& ActionBinding :
			InputBindings->ActionBindings)
		{
			for (const FEasyInputActionKey& Key :
				ActionBinding.GetKeys())
			{
				FInputKeyBinding KB(FInputChord(
					Key.GetKey(), Key.GetShift(),
					Key.GetCtrl(), Key.GetAlt(), false),
					ActionBinding.GetInputEvent());
				KB.KeyDelegate.BindDelegate(
					Character, ActionBinding.GetFunctionName());
				PlayerController->InputComponent->KeyBindings.Emplace(
					MoveTemp(KB));
			}
		}

		for (const FEasyInputAxisBinding& AxisBinding :
			InputBindings->AxisBindings)
		{
			for (const FKey& Key : AxisBinding.GetKeys())
			{
				FInputAxisKeyMapping Mapping(
					AxisBinding.GetFunctionName(),
					Key,
					AxisBinding.GetScale());
				PlayerController->PlayerInput->AxisMappings.Emplace(
					MoveTemp(Mapping));

				FInputAxisBinding AB(AxisBinding.GetFunctionName());
				AB.AxisDelegate.BindDelegate(
					Character, AxisBinding.GetFunctionName());
				PlayerController->InputComponent->AxisBindings.Emplace(
					MoveTemp(AB));
			}
		}

		InputTags.AddTag(InputBindings->InputTag);
	}
}
