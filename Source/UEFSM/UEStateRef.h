// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"

#include "UEStatePhase.h"

#include "UEStateRef.generated.h"

/// <summary>
/// This holds a reference to a IUEFiniteStateInterface as well as the 
/// current EUEStatePhase of the specific state. This is required as 
/// states are intended to be reusable and focus on the logic of the 
/// behaviour in that FSM.
/// </summary>
USTRUCT(BlueprintType)
struct UEFSM_API FUEStateRef
{
	GENERATED_BODY()

	/// <summary>A reference to an IUEFIniteStateInterfaces' object.</summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UObject> State;

	/// <summary>The phase of this state in the owning FSM.</summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUEStatePhase Phase;

	/// <summary>Default c'tor.</summary>
	FUEStateRef() : State(nullptr), Phase(EUEStatePhase::None) {}

	/// <summary>C'tor which sets the state to the object contained in an IUEFiniteStateInterface.</summary>
	/// <param name="Value">The Interface's object.</param>
	FUEStateRef(UObject* Value) : State(Value), Phase(EUEStatePhase::None) {}
};
