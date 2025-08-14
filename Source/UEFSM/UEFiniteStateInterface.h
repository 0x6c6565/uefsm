// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "UEFiniteStateInterface.generated.h"

/// <summary>Interface def for States in the UEFSM ecosystem. Can be assigned in Blueprints/cxx.</summary>
UINTERFACE(MinimalAPI, Blueprintable)
class UUEFiniteStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UEFSM_API IUEFiniteStateInterface
{
	GENERATED_BODY()

public:

	/// <summary>This method is called when the state is first entered.</summary>
	/// <param name="Machine">The interface to the FSM that owns this state.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Enter(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);

	/// <summary>When the first tick is called with this as the active state, this method is invoked, otherwise Execute() is.</summary>
	/// <param name="Machine">The owning FSM interface.</param>
	/// <param name="Delta">Elapsed seconds since the last Update() call.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FirstExecute(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	/// <summary>After the first tick, with this state active, this method is called.</summary>
	/// <param name="Machine">The owning FSM interface.</param>
	/// <param name="Delta">Elapsed seconds since the last Execute().</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Execute(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	/// <summary>When a state is removed from the active state collection this method will be invoked.</summary>
	/// <param name="Machine">The interface to the FMS that owns this state.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Exit(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);
};
