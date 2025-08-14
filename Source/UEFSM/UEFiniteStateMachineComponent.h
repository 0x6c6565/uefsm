// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "UEFiniteStateMachineInterface.h"

#include "UEFSMResult.h"
#include "UEStateRef.h"

#include "UEFiniteStateMachineComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UEFSM_API UUEFiniteStateMachineComponent : public UActorComponent, public IUEFiniteStateMachineInterface
{
	GENERATED_BODY()

public:

	UUEFiniteStateMachineComponent();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<UObject>, TObjectPtr<UObject>> States;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UObject> InitialClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess="true"))
	TArray<FUEStateRef> Current;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TimeInState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsPaused;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool AutoLoadComponentStates;

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
	void GetCurrent(TScriptInterface<class IUEFiniteStateInterface>& State, EUEFSMResult& Pins) const;

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

protected:

	virtual float GetTimeInState_Implementation() const;
	virtual void AddStates_Implementation(UPARAM(ref) const TArray<TScriptInterface<class IUEFiniteStateInterface>>& Collection);
	virtual void AddState_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateInterface>& State);
	virtual void SetInitialState_Implementation(TSubclassOf<UObject> State);
	virtual void Pause_Implementation(bool Value);
	virtual bool HasCurrent_Implementation() const;
	virtual bool IsCurrent_Implementation(TSubclassOf<UObject> State) const;
	virtual void GetCurrent_Implementation(TScriptInterface<class IUEFiniteStateInterface>& State, EUEFSMResult& Pins) const;
	virtual bool TryGetCurrent_Implementation(TScriptInterface<class IUEFiniteStateInterface>& State) const;
	virtual bool Contains_Implementation(TSubclassOf<UObject> State) const;
	virtual void Push_Implementation(TSubclassOf<UObject> State);
	virtual void Pop_Implementation();
	virtual void Change_Implementation(TSubclassOf<UObject> State);

	bool HasNoPhase(const FUEStateRef &StateRef) const;
	bool HasEntered(const FUEStateRef& StateRef) const;
	bool HasExecuted(const FUEStateRef& StateRef) const;
	bool HasEnteredOrExecuted(const FUEStateRef& StateRef) const;
	bool HasExited(const FUEStateRef& StateRef) const;

	bool ComparePhase(const FUEStateRef& StateRef, const EUEStatePhase &Phase) const;

	virtual void Enter_Implementation();
	virtual void Execute_Implementation(float Delta);
	virtual void Exit_Implementation();
};
