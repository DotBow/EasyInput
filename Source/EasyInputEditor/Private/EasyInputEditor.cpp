// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#include "EasyInputEditor.h"

#include "AssetToolsModule.h"
#include "EasyInputEditorStyle.h"
#include "IAssetTools.h"
#include "EasyInputKeyBindingsAsset.h"
#include "Customization/EasyInputKeyBindingsCustomization.h"


#define LOCTEXT_NAMESPACE "FEasyInputEditorModule"

void FEasyInputEditorModule::StartupModule()
{
	FEasyInputEditorStyle::Get();

	IAssetTools& AssetTools =
		FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const EAssetTypeCategories::Type EasyInputCategoryBit =
		AssetTools.RegisterAdvancedAssetCategory(
			FName(TEXT("Easy Input")),
			LOCTEXT("EasyInputCategory", "Easy Input"));

	AssetTools.RegisterAssetTypeActions(
		MakeShareable(new FEasyInputBindingsActions(
			EasyInputCategoryBit)));

	FPropertyEditorModule& PropertyModule =
		FModuleManager::LoadModuleChecked
		<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomPropertyTypeLayout(
		FEasyInputActionKey::StaticStruct()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(
			&FEasyInputActionKeyCustomization::MakeInstance));

	PropertyModule.RegisterCustomClassLayout(
		UEasyInputBindings::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(
			&FEasyInputBindingsCustomization::MakeInstance));
}

void FEasyInputEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEasyInputEditorModule, EasyInputEditor)
