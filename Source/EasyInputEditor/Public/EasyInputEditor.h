// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

#pragma once
#include "Modules/ModuleManager.h"


class FEasyInputEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
