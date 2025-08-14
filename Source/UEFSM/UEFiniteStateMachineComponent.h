// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "UEFiniteStateMachineInterface.h"

#include "UEFSMResult.h"
#include "UEStateRef.h"

#include "UEFiniteStateMachineComponent.generated.h"

/// <summary>
/// An implementation of an FSM that follows the Actor/ActorComponent architecture.
/// </summary>
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UEFSM_API UUEFiniteStateMachineComponent : public UActorComponent, public IUEFiniteStateMachineInterface
{
	GENERATED_BODY()

public:

	/// <summary>Default c'tor.</summary>
	UUEFiniteStateMachineComponent();

protected:

	/// <summary>The contained states in the FSM.</summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<UObject>, TObjectPtr<UObject>> States;

	/// <summary>The class type of the initial state.</summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UObject> InitialClass;

	/// <summary>
	///	The stack of current state references.
	/// The container, FUEStateRef contains the phase of the state allowing it to 
	/// remain discretely separate from the state. While not strictly required for
	/// components on the actor, this allows for more freedom in that states do not 
	/// have to hold data and can be reuses amongst machines.
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess="true"))
	TArray<FUEStateRef> Current;

	/// <summary>The time in the current state.</summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TimeInState;

	/// <summary>Storage for the FSM pause state.</summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsPaused;

	/// <summary>
	/// If true, when BeginPlay() is called this FSM will look for siblings 
	///	that implement the State Interface and add them.
	///</summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool AutoLoadComponentStates;

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
	void GetCurrent(TScriptInterface<class IUEFiniteStateInterface>& State, EUEFSMResult& Pins) const;

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

protected:

	/// <summary>See GetTimeInState(). Override this if specializing in cxx.</summary>
	/// <returns></returns>
	virtual float GetTimeInState_Implementation() const;
	/// <summary>See AddStates(). Override this if specializing in cxx.</summary>
	/// <param name="Collection">The array of states to add.</param>
	virtual void AddStates_Implementation(UPARAM(ref) const TArray<TScriptInterface<class IUEFiniteStateInterface>>& Collection);
	/// <summary>See AddState(). Override this if specializing in cxx.</summary>
	/// <param name="State">The state to add.</param>
	virtual void AddState_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateInterface>& State);
	/// <summary>See SetInitialState(). Override this if specializing in cxx.</summary>
	/// <param name="State">The class type of the state that should be the initial state.</param>
	virtual void SetInitialState_Implementation(TSubclassOf<UObject> State);
	/// <summary>See Pause(). Override this if specializing in cxx.</summary>
	/// <param name="Value">To pause pass true; otherwise pass false.</param>
	virtual void Pause_Implementation(bool Value);
	/// <summary>See HasCurrent(). Override this if specializing in cxx.</summary>
	/// <returns>Whether or not there is a current state.</returns>
	virtual bool HasCurrent_Implementation() const;
	/// <summary>See IsCurrent(). Override this if specializing in cxx.</summary>
	/// <param name="State">The state to compare to current.</param>
	/// <returns>True, if the state passed in is the current state; false otherwise.</returns>
	virtual bool IsCurrent_Implementation(TSubclassOf<UObject> State) const;
	/// <summary>See GetCurrent(). Override this if specializing in cxx.</summary>
	/// <param name="State">The pointer to assign the current state to.</param>
	/// <param name="Pins">The resulting exec (Valid/Invalid.)</param>
	virtual void GetCurrent_Implementation(TScriptInterface<class IUEFiniteStateInterface>& State, EUEFSMResult& Pins) const;
	/// <summary>See TryGetCurrent(). Override this if specializing in cxx.</summary>
	/// <param name="State">Object to hold the current state pointer.</param>
	/// <returns>The result of getting the current state.</returns>
	virtual bool TryGetCurrent_Implementation(TScriptInterface<class IUEFiniteStateInterface>& State) const;
	/// <summary>See Contains(). Override this if specializing in cxx.</summary>
	/// <param name="State">The state to look for.</param>
	/// <returns>The result of the comparison.</returns>
	virtual bool Contains_Implementation(TSubclassOf<UObject> State) const;
	/// <summary>See Push(). Override this if specializing in cxx.</summary>
	/// <param name="State">The state to add as current.</param>
	virtual void Push_Implementation(TSubclassOf<UObject> State);
	/// <summary>See Pop(). Override this if specializing in cxx.</summary>
	virtual void Pop_Implementation();
	/// <summary>See Change(). Override this if specializing in cxx.</summary>
	/// <param name="State">The state to change current to.</param>
	virtual void Change_Implementation(TSubclassOf<UObject> State);

	// //////////////// //
	// HELPER FUNCTIONS //
	bool HasNoPhase(const FUEStateRef &StateRef) const;
	bool HasEntered(const FUEStateRef& StateRef) const;
	bool HasExecuted(const FUEStateRef& StateRef) const;
	bool HasEnteredOrExecuted(const FUEStateRef& StateRef) const;
	bool HasExited(const FUEStateRef& StateRef) const;

	bool ComparePhase(const FUEStateRef& StateRef, const EUEStatePhase &Phase) const;
	// HELPER FUNCTIONS //
	// //////////////// //

	/// <summary>See Enter(). Override this if specializing in cxx.</summary>
	virtual void Enter_Implementation();
	/// <summary>See Execute(). Override this if specializing in cxx.</summary>
	/// <param name="Delta">Elapsed seconds.</param>
	virtual void Execute_Implementation(float Delta);
	/// <summary>See Exit(). Override this if specializing in cxx.</summary>
	virtual void Exit_Implementation();
};
