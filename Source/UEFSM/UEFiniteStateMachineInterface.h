// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "UEFSMResult.h"

#include "UEFiniteStateMachineInterface.generated.h"

/// <summary>
/// The interface definition for the Finite State Machine object.
/// Blueprintable for prototyping as well as '_Implementation' enabled
/// for cxx specializing.
/// </summary>
UINTERFACE(MinimalAPI, Blueprintable)
class UUEFiniteStateMachineInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UEFSM_API IUEFiniteStateMachineInterface
{
	GENERATED_BODY()

public:

	/// <summary>Get the total number of seconds in the current state.</summary>
	/// <returns>The elapsed seconds in the current state.</returns>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ReturnDisplayName = "Value", CompactNodeTitle = "Time in State"))
	float GetTimeInState() const;

	/// <summary>Add a number of states to the FSM.</summary>
	/// <param name="Collection">The array of state interfaces to add.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddStates(UPARAM(ref) const TArray<TScriptInterface<class IUEFiniteStateInterface>>& Collection);

	/// <summary>Add a single state to the FSM.</summary>
	/// <param name="State">The interface for the state to add.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddState(UPARAM(ref) const TScriptInterface<class IUEFiniteStateInterface>& State);

	/// <summary>Sets the initial state class for the FSM.</summary>
	/// <param name="State">The class type of the state interface to use as the initial state.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetInitialState(TSubclassOf<UObject> State);

	/// <summary>Stop the update functionality of the state machine.</summary>
	/// <param name="Value">True to stop; false to continue.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pause(bool Value);

	/// <summary>Is there a currently active state?</summary>
	/// <returns>Whether or not there is a current state.</returns>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool HasCurrent() const;

	/// <summary>Is the current state equal the the state that is passed in?</summary>
	/// <param name="State">The state to compare to the currently executing state.</param>
	/// <returns>The result of the comparison.</returns>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsCurrent(TSubclassOf<UObject> State) const;

	/// <summary>Get the interface of the currently active state.</summary>
	/// <param name="State">The interface that will be assigned from the current state if valid.</param>
	/// <param name="Pins">This enables multiple exec pins as output. Valid/invalid for the current state.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure = false, meta = (ExpandEnumAsExecs = "Pins"))
	void GetCurrent(TScriptInterface<class IUEFiniteStateInterface> &State, EUEFSMResult & Pins) const;

	/// <summary>Identical to GetCurrent() only this returns a bool instead of multiple exec pins.</summary>
	/// <param name="State">The interface that will be assigned the currect state.</param>
	/// <returns>True if the state is valid; false otherwise.</returns>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TryGetCurrent(TScriptInterface<class IUEFiniteStateInterface>& State) const;

	/// <summary>Is the argument 'State' contained in the FSM's collection of states?</summary>
	/// <param name="State">The state for which to look.</param>
	/// <returns>The result of the check.</returns>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Contains(TSubclassOf<UObject> State) const;

	/// <summary>Places a new active state onto the stack without removing the previous one.</summary>
	/// <param name="State">The new state.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Push(TSubclassOf<UObject> State);

	/// <summary>Removes the currently active state if valid.</summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pop();

	/// <summary>
	/// Change the current state to the argument State. Should call Exit() on 
	/// the current state if it exists and Enter() on the new 'State' if it is 
	/// valid.
	/// </summary>
	/// <param name="State">The new state to switch to.</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Change(TSubclassOf<UObject> State);

	/// <summary>Handler for entering the new current state.</summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Enter();

	/// <summary>Handler for executing the current state.</summary>
	/// <param name="Delta">Elapsed seconds since last Execute().</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Execute(float Delta);

	/// <summary>Handler for exiting the current state.</summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Exit();
};
