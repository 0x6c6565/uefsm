// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "UEFiniteStateInterface.generated.h"

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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Enter(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FirstExecute(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Execute(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Exit(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);
};
