// Copyright (C) Dreamer's Tail

#include "EasyInputComponent.h"

#include "CommonUserWidget.h"
#include "EasyInputBindings.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"
#include "Input/CommonUIInputTypes.h"


UEasyInputComponent::UEasyInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEasyInputComponent::RegisterWidgetInputs(
	UCommonUserWidget* Widget) const
{
	for (const FUIInputAction& InputAction : InputBindings->GetUIActionBindings())
	{
		FSimpleDelegate Delegate;
		Delegate.BindUFunction(Widget, "Test");
		const FUIActionBindingHandle Handle =
			Widget->RegisterUIActionBinding(FBindUIActionArgs(
			InputAction.ActionTag, false,
			Delegate));
	}
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
	const TObjectPtr<ACharacter>& Character) const
{
	for (const FEasyInputActionBinding& ActionBinding :
		InputBindings->GetActionBindings())
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
		InputBindings->GetAxisBindings())
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
}
