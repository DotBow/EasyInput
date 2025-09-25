// Copyright (C) MAG Development Ltd. 2024. All Rights Reserved.
// Authors: @o.stepanov

#include "EasyInputEditorStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"


FName FEasyInputEditorStyle::StyleName("EasyInputEditorStyle");

FEasyInputEditorStyle::FEasyInputEditorStyle()
	: FSlateStyleSet(StyleName)
{
	FSlateStyleSet::SetContentRoot(
		IPluginManager::Get().FindPlugin("EasyInput")->GetBaseDir() /
		TEXT("Resources/Icons"));
	FSlateStyleSet::SetCoreContentRoot(
		FPaths::EngineContentDir() / TEXT("Editor/Slate"));

	Set("ClassThumbnail.EasyInputBindings",
		new IMAGE_BRUSH("EasyInputBindings", FVector2D(96, 96)));

	Set("EasyInputBinding.Description",
		new IMAGE_BRUSH("EasyInputBindingDescription", FVector2D(32, 32)));
	Set("EasyInputBinding.Function",
		new IMAGE_BRUSH("EasyInputBindingFunction", FVector2D(32, 32)));
	Set("EasyInputBinding.Event",
		new IMAGE_BRUSH("EasyInputBindingEvent", FVector2D(32, 32)));
	Set("EasyInputBinding.Keys",
		new IMAGE_BRUSH("EasyInputBindingKeys", FVector2D(32, 32)));

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FEasyInputEditorStyle::~FEasyInputEditorStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}

FEasyInputEditorStyle& FEasyInputEditorStyle::Get()
{
	static FEasyInputEditorStyle Inst;
	return Inst;
}
