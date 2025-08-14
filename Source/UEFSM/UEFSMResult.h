// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"

#include "UEFSMResult.generated.h"

/// <summary>Helper enum for multi-exec functionality.</summary>
UENUM(BlueprintType)
enum class EUEFSMResult : uint8
{
	Valid UMETA(DisplayName = "Valid"),
	Invalid UMETA(DisplayName = "Invalid")
};
