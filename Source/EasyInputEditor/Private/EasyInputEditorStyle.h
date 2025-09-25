// Copyright (C) MAG Development Ltd. 2024. All Rights Reserved.
// Authors: @o.stepanov

#pragma once
#include "Styling/SlateStyle.h"


class FEasyInputEditorStyle : public FSlateStyleSet
{
public:
	static FName StyleName;
	static FEasyInputEditorStyle& Get();

private:
	FEasyInputEditorStyle();
	virtual ~FEasyInputEditorStyle() override;
};
