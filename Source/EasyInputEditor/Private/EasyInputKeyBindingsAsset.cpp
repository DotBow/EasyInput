// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#include "EasyInputKeyBindingsAsset.h"


UEasyInputBindingsFactory::UEasyInputBindingsFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UEasyInputBindings::StaticClass();
}

bool UEasyInputBindingsFactory::ConfigureProperties()
{
	return true;
}

UObject* UEasyInputBindingsFactory::FactoryCreateNew(
	UClass* Class,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn)
{
	return NewObject<UDataAsset>(
		InParent,
		UEasyInputBindings::StaticClass(),
		Name,
		Flags | RF_Transactional);
}
