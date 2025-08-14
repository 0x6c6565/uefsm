// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#include "UEFSM.h"

#define LOCTEXT_NAMESPACE "FUEFSMModule"

void FUEFSMModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUEFSMModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUEFSMModule, UEFSM)