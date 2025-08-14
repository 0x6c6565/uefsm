// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "UEFiniteStateInterface.h"

#include "UEStatePhase.h"

#include "UEFiniteStateComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, Abstract, meta = (BlueprintSpawnableComponent))
class UEFSM_API UUEFiniteStateComponent : public UActorComponent, public IUEFiniteStateInterface
{
	GENERATED_BODY()

	friend class UEFiniteStateMachineComponent;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EUEStatePhase Phase;

public:

	UUEFiniteStateComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Enter(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FirstExecute(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Execute(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Exit(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);

protected:

	virtual void Enter_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);

	virtual void FirstExecute_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	virtual void Execute_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	virtual void Exit_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);
};
