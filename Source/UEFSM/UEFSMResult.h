// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UEFSMResult.generated.h"

UENUM(BlueprintType)
enum class EUEFSMResult : uint8
{
	Valid UMETA(DisplayName = "Valid"),
	Invalid UMETA(DisplayName = "Invalid")
};
