// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#pragma once
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEasyInput, All, All);


class FEasyInputModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
