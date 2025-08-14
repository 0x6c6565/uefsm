// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UEStatePhase.generated.h"

UENUM(BlueprintType)
enum class EUEStatePhase : uint8
{
	None UMETA(DisplayName = "None"),
	Entered UMETA(DisplayName = "Entered"),
	Executed UMETA(DisplayName = "Executed"),
	Exited  UMETA(DisplayName = "Exited")
};
