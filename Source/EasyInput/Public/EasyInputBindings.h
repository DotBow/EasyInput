// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#pragma once
#include "GameplayTagContainer.h"
#include "EasyInputBindings.generated.h"


USTRUCT(NotBlueprintable, NotBlueprintType)
struct FEasyInputBinding
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FString FunctionName;

public:
	FEasyInputBinding(
		const FString& InFunction =
			FString("Function not provided"))
		: FunctionName(InFunction) {}

	FName GetFunctionName() const
	{
		return *FunctionName;
	}

#if WITH_EDITOR
	void SetFunctionName(const FString InName)
	{
		FunctionName = InName;
	}

	static FName GetFunctionMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputBinding, FunctionName);
	}
#endif
};


USTRUCT(NotBlueprintable, NotBlueprintType)
struct FEasyInputActionKey
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FKey Key;

	UPROPERTY(EditAnywhere)
	bool bShift;

	UPROPERTY(EditAnywhere)
	bool bCtrl;

	UPROPERTY(EditAnywhere)
	bool bAlt;

public:
	FEasyInputActionKey(
		const FKey& InKey = {},
		const bool bInShift = false,
		const bool bInCtrl = false,
		const bool bInAlt = false)
		: Key(InKey)
		, bShift(bInShift)
		, bCtrl(bInCtrl)
		, bAlt(bInAlt) {}

	FKey GetKey() const
	{
		return Key;
	}

	bool GetShift() const
	{
		return bShift;
	}

	bool GetCtrl() const
	{
		return bCtrl;
	}

	bool GetAlt() const
	{
		return bAlt;
	}

#if WITH_EDITOR
	static FName GetKeyMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputActionKey, Key);
	}

	static FName GetShiftMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputActionKey, bShift);
	}

	static FName GetCtrlMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputActionKey, bCtrl);
	}

	static FName GetAltMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputActionKey, bAlt);
	}
#endif
};


USTRUCT(NotBlueprintable, NotBlueprintType)
struct FEasyInputActionBinding : public FEasyInputBinding
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TArray<FEasyInputActionKey> Keys;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EInputEvent> InputEvent;

public:
	FEasyInputActionBinding(
		const FString& InFunction =
			FString("Function not provided"),
		const TArray<FEasyInputActionKey>& InKeys =
			{ FEasyInputActionKey() },
		const TEnumAsByte<EInputEvent> InInputEvent = IE_Pressed)
		: Super(InFunction)
		, Keys(InKeys)
		, InputEvent(InInputEvent) {}

	EInputEvent GetInputEvent() const
	{
		return InputEvent;
	}

	TArray<FEasyInputActionKey> GetKeys() const
	{
		return Keys;
	}

	TArray<FEasyInputActionKey>& GetKeysRef()
	{
		return Keys;
	}

#if WITH_EDITOR
	static FName GetKeysMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputActionBinding, Keys);
	}

	static FName GetInputEventMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputActionBinding, InputEvent);
	}
#endif
};


#if WITH_EDITOR
UENUM()
enum class EEasyInputBindingType : uint8
{
	Action = 1 << 0,
	Axis   = 2 << 0,
};
#endif


USTRUCT(NotBlueprintable, NotBlueprintType)
struct FEasyInputAxisBinding : public FEasyInputBinding
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TArray<FKey> Keys;

	UPROPERTY(EditAnywhere)
	float Scale;

public:
	FEasyInputAxisBinding(
		const FString& InFunction =
			FString("Function not provided"),
		const TArray<FKey>& InKeys = { FKey() },
		const float InScale = 1.f)
		: Super(InFunction)
		, Keys(InKeys)
		, Scale(InScale) {}

	float GetScale() const
	{
		return Scale;
	}

	TArray<FKey> GetKeys() const
	{
		return Keys;
	}

	TArray<FKey>& GetKeysRef()
	{
		return Keys;
	}

#if WITH_EDITOR
	static FName GetKeysMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputAxisBinding, Keys);
	}

	static FName GetScaleMember()
	{
		return GET_MEMBER_NAME_CHECKED(
			FEasyInputAxisBinding, Scale);
	}
#endif
};


UCLASS(NotBlueprintable, NotBlueprintType)
class EASYINPUT_API UEasyInputBindings : public UDataAsset
{
	GENERATED_BODY()

public:
	UEasyInputBindings();

	UPROPERTY(EditAnywhere, meta=(DisallowCreateNew))
	FGameplayTag InputTag;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, meta=(DisallowCreateNew))
	TSoftClassPtr<AActor> FunctionsSource;
#endif

	UPROPERTY(EditAnywhere, meta=(NoElementDuplicate, EditFixedOrder))
	TArray<FEasyInputActionBinding> ActionBindings;

	UPROPERTY(EditAnywhere, meta=(NoElementDuplicate, EditFixedOrder))
	TArray<FEasyInputAxisBinding> AxisBindings;

	static void SetupKeyBindings(
		const TObjectPtr<APlayerController>& PlayerController,
		UObject* Object,
		const TObjectPtr<UEasyInputBindings>& KeyBindings);

#if WITH_EDITOR
	static FName GetBindingsMember(const EEasyInputBindingType Type)
	{
		if (Type == EEasyInputBindingType::Action)
			return GET_MEMBER_NAME_CHECKED(UEasyInputBindings, ActionBindings);
		if (Type == EEasyInputBindingType::Axis)
			return GET_MEMBER_NAME_CHECKED(UEasyInputBindings, AxisBindings);

		return NAME_None;
	}

	void AddBinding(const EEasyInputBindingType Type)
	{
		Modify();

		if (Type == EEasyInputBindingType::Action)
			ActionBindings.Add(FEasyInputActionBinding());
		else if (Type == EEasyInputBindingType::Axis)
			AxisBindings.Add(FEasyInputAxisBinding());
	}

	void DeleteBinding(
		const int32 BindingIdx,
		const EEasyInputBindingType Type)
	{
		Modify();

		if (Type == EEasyInputBindingType::Action)
			ActionBindings.RemoveAt(BindingIdx);
		else if (Type == EEasyInputBindingType::Axis)
			AxisBindings.RemoveAt(BindingIdx);
	}

	void EmptyBindings(
		const EEasyInputBindingType Type)
	{
		Modify();

		if (Type == EEasyInputBindingType::Action)
			ActionBindings.Empty();
		else if (Type == EEasyInputBindingType::Axis)
			AxisBindings.Empty();
	}

	void AddBindingKey(
		const int32 BindingKey,
		const EEasyInputBindingType Type)
	{
		Modify();

		if (Type == EEasyInputBindingType::Action)
			ActionBindings[BindingKey].GetKeysRef().Add(FEasyInputActionKey());
		else if (Type == EEasyInputBindingType::Axis)
			AxisBindings[BindingKey].GetKeysRef().Add(FKey());
	}

	void DeleteBindingKey(
		const int32 BindingKey,
		const int32 KeyIdx,
		const EEasyInputBindingType Type)
	{
		if (CanDeleteBindingKey(BindingKey, Type))
		{
			Modify();

			if (Type == EEasyInputBindingType::Action)
				ActionBindings[BindingKey].GetKeysRef().RemoveAt(KeyIdx);
			else if (Type == EEasyInputBindingType::Axis)
				AxisBindings[BindingKey].GetKeysRef().RemoveAt(KeyIdx);
		}
	}

	bool CanDeleteBindingKey(
		const int32 BindingKey,
		const EEasyInputBindingType Type) const
	{
		if (Type == EEasyInputBindingType::Action)
			return ActionBindings[BindingKey].GetKeys().Num() > 1;
		if (Type == EEasyInputBindingType::Axis)
			return AxisBindings[BindingKey].GetKeys().Num() > 1;

		return false;
	}

	void SetBindingFunction(
		const int32 BindingKey,
		const EEasyInputBindingType Type,
		const FString& InFunction)
	{
		Modify();

		if (Type == EEasyInputBindingType::Action)
			ActionBindings[BindingKey].SetFunctionName(InFunction);
		if (Type == EEasyInputBindingType::Axis)
			AxisBindings[BindingKey].SetFunctionName(InFunction);
	}

	TArray<FString> GetSourceFunctions(
		const EEasyInputBindingType Type) const;
#endif
};
