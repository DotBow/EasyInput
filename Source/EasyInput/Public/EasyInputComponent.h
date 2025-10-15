// Copyright (C) Dreamer's Tail

#pragma once

#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "EasyInputComponent.generated.h"


UCLASS(Within=Character, ClassGroup=(Input), meta=(BlueprintSpawnableComponent))
class EASYINPUT_API UEasyInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEasyInputComponent();

	FGameplayTag GetActiveInputTag() const;

	void SetActiveInputTag(
		const FGameplayTag& InActiveInputTag);

private:
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<class UEasyInputBindings> InputBindings;

	UPROPERTY()
	FGameplayTagContainer InputTags;

	UPROPERTY(VisibleAnywhere)
	FGameplayTag ActiveInputTag;

protected:
	virtual void BeginPlay() override;

	void SetInputBindings(
		const TObjectPtr<APlayerController>& PlayerController,
		UEasyInputBindings* InInputBindings,
		UObject* Object);
};
