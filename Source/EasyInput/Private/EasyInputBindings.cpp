// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#include "EasyInputBindings.h"
#include "GameFramework/PlayerInput.h"


UEasyInputBindings::UEasyInputBindings()
{
}

void UEasyInputBindings::SetupKeyBindings(
	const TObjectPtr<APlayerController>& PlayerController,
	UObject* Object,
	const TObjectPtr<UEasyInputBindings>& KeyBindings)
{
	if (!ensureMsgf(PlayerController,
		TEXT("Player Controller is invalid!")))
		return;

	if (!ensureMsgf(KeyBindings,
		TEXT("Key Bindings asset is invalid!")))
		return;

	for (const FEasyInputActionBinding& ActionBinding :
		KeyBindings->ActionBindings)
	{
		for (const FEasyInputActionKey& Key :
			ActionBinding.GetKeys())
		{
			FInputKeyBinding KB(FInputChord(
				Key.GetKey(), Key.GetShift(),
				Key.GetCtrl(), Key.GetAlt(), false),
				ActionBinding.GetInputEvent());
			KB.KeyDelegate.BindDelegate(
				Object, ActionBinding.GetFunctionName());
			PlayerController->InputComponent->KeyBindings.Emplace(
				MoveTemp(KB));
		}
	}

	for (const FEasyInputAxisBinding& AxisBinding :
		KeyBindings->AxisBindings)
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
				Object, AxisBinding.GetFunctionName());
			PlayerController->InputComponent->AxisBindings.Emplace(
				MoveTemp(AB));
		}
	}
}

#if WITH_EDITOR
TArray<FString> UEasyInputBindings::GetSourceFunctions(
	const EEasyInputBindingType Type) const
{
	TArray<FString> FunctionNames;

	if (!FunctionsSource.IsNull())
	{
		UClass* LoadedClass = FunctionsSource.LoadSynchronous();
		const UStruct* Struct = Cast<UStruct>(LoadedClass);

		for (TFieldIterator<UFunction> FuncIt(Struct);
			FuncIt; ++FuncIt)
		{
			if (const UFunction* Function = *FuncIt; Function &&
				Function->HasAnyFunctionFlags(FUNC_BlueprintEvent) &&
				Function->HasMetaData("EasyInputFunction"))
			{
				if ((Type == EEasyInputBindingType::Action && Function->NumParms == 0) ||
					(Type == EEasyInputBindingType::Axis && Function->NumParms > 0))
				{
					FString FunctionName = Function->GetName();
					FunctionNames.Add(FunctionName);
				}
			}
		}
	}

	return FunctionNames;
}
#endif
