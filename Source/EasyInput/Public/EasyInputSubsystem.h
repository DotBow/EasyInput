// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Subsystems/EngineSubsystem.h"
#include "EasyInputSubsystem.generated.h"

class UEasyInputBindings;


UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Default);


UCLASS()
class EASYINPUT_API UEasyInputSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(
		FSubsystemCollectionBase& Collection) override;

	void SetInputBindings(
		const TObjectPtr<APlayerController>& PlayerController,
		UEasyInputBindings* InputBindings,
		UObject* Object);

	FGameplayTag GetActiveInputTag() const;
	void SetActiveInputTag(
		const FGameplayTag& InActiveInputTag);

private:
	UPROPERTY()
	FGameplayTagContainer InputTags;

	UPROPERTY()
	FGameplayTag ActiveInputTag;
};


extern EASYINPUT_API UEasyInputSubsystem* EasyInputSubsystem;
