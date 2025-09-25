// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#pragma once

#include "AssetTypeActions_Base.h"
#include "AssetTypeCategories.h"
#include "Factories/DataAssetFactory.h"
#include "EasyInputBindings.h"
#include "EasyInputKeyBindingsAsset.generated.h"


UCLASS()
class EASYINPUTEDITOR_API UEasyInputBindingsFactory : public UDataAssetFactory
{
	GENERATED_BODY()

	UEasyInputBindingsFactory();

	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(
		UClass* Class,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;
};


class EASYINPUTEDITOR_API FEasyInputBindingsActions : public FAssetTypeActions_Base
{
public:
	FEasyInputBindingsActions(EAssetTypeCategories::Type AssetCategory)
		: AssetCategory(AssetCategory) {}

	virtual UClass* GetSupportedClass() const override
	{
		return UEasyInputBindings::StaticClass();
	}

	virtual FText GetName() const override
	{
		return INVTEXT("Key Bindings");
	}

	virtual FColor GetTypeColor() const override
	{
		return FColor::FromHex("ffb627");
	}

	virtual uint32 GetCategories() override
	{
		return AssetCategory;
	}

private:
	EAssetTypeCategories::Type AssetCategory =
		EAssetTypeCategories::Misc;
};
