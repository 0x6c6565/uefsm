// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#pragma once

#include "Modules/ModuleManager.h"

class FUEFSMModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
