// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "UEFSMResult.h"

#include "UEFiniteStateMachineInterface.generated.h"

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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ReturnDisplayName = "Value", CompactNodeTitle = "Time in State"))
	float GetTimeInState() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddStates(UPARAM(ref) const TArray<TScriptInterface<class IUEFiniteStateInterface>>& Collection);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddState(UPARAM(ref) const TScriptInterface<class IUEFiniteStateInterface>& State);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetInitialState(TSubclassOf<UObject> State);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pause(bool Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool HasCurrent() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsCurrent(TSubclassOf<UObject> State) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure = false, meta = (ExpandEnumAsExecs = "Pins"))
	void GetCurrent(TScriptInterface<class IUEFiniteStateInterface> &State, EUEFSMResult & Pins) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TryGetCurrent(TScriptInterface<class IUEFiniteStateInterface>& State) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Contains(TSubclassOf<UObject> State) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Push(TSubclassOf<UObject> State);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pop();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Change(TSubclassOf<UObject> State);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Enter();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Execute(float Delta);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Exit();
};
