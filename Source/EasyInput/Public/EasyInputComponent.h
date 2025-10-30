// Copyright (C) Dreamer's Tail

#pragma once

#include "Components/ActorComponent.h"
#include "EasyInputComponent.generated.h"


UCLASS(Within=PlayerController, ClassGroup=(Input), meta=(BlueprintSpawnableComponent))
class EASYINPUT_API UEasyInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEasyInputComponent();

	void RegisterWidgetInputs(
		class UCommonUserWidget* Widget) const;

private:
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<class UEasyInputBindings> InputBindings;

protected:
	virtual void BeginPlay() override;

	void SetInputBindings(
		const TObjectPtr<APlayerController>& PlayerController,
		const TObjectPtr<ACharacter>& Character) const;
};
