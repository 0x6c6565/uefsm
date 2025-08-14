// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"

#include "UEStatePhase.generated.h"

/// <summary>
/// States exist in one of four states:
///		- None this state isn't in use
///		- Entered this state has been entered
///		- Executed this state IS executing
///			Set prior entry into first execution
///		- Exited this state will invoke it's Exit()
/// </summary>
UENUM(BlueprintType)
enum class EUEStatePhase : uint8
{
	None UMETA(DisplayName = "None"),
	Entered UMETA(DisplayName = "Entered"),
	Executed UMETA(DisplayName = "Executed"),
	Exited  UMETA(DisplayName = "Exited")
};
