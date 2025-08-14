// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UEStatePhase.h"

#include "UEStateRef.generated.h"

USTRUCT(BlueprintType)
struct UEFSM_API FUEStateRef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UObject> State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUEStatePhase Phase;

	FUEStateRef() : State(nullptr), Phase(EUEStatePhase::None) {}
	FUEStateRef(UObject* Value) : State(Value), Phase(EUEStatePhase::None) {}
};
