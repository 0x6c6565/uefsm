// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "UEFiniteStateInterface.h"

#include "UEStatePhase.h"

#include "UEFiniteStateComponent.generated.h"

/// <summary>
/// UEFuniteStateComponent is an implementation to demonstrate the 
/// GameObject/MonoBehaviour style component-based design approach.
/// 
/// Simply specialize this class for each unique state required.
/// </summary>
UCLASS(Blueprintable, BlueprintType, Abstract, meta = (BlueprintSpawnableComponent))
class UEFSM_API UUEFiniteStateComponent : public UActorComponent, public IUEFiniteStateInterface
{
	GENERATED_BODY()

	friend class UEFiniteStateMachineComponent; // For protected access.

public:

	/// <summary>Default c'tor</summary>
	UUEFiniteStateComponent();

	/// <summary>This function doesn't really need to be here as it only calls the base impl...</summary>
	/// <param name="DeltaTime">Elapsed seconds.</param>
	/// <param name="TickType">When the tick is executed.</param>
	/// <param name="ThisTickFunction">the tick method.</param>
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	/// <summary>This function doesn't really need to be here as it only calls the base impl...</summary>
	virtual void BeginPlay() override;

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

protected:

	/// <summary>See Enter(). If deriving in cxx use override this method instead of Enter().</summary>
	/// <param name="Machine">The owning FSM.</param>
	virtual void Enter_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);

	/// <summary>See FirstExecute(). If deriving in cxx use override this method instead of FirstExecute().</summary>
	/// <param name="Machine">The owning FSM.</param>
	/// <param name="Delta">Elapsed seconds.</param>
	virtual void FirstExecute_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	/// <summary>See Execute(). If deriving in cxx use override this method instead of Execute().</summary>
	/// <param name="Machine">The owning FSM.</param>
	/// <param name="Delta">Elapsed seconds.</param>
	virtual void Execute_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta);

	/// <summary>See Exit(). If deriving in cxx use override this method instead of Exit().</summary>
	/// <param name="Machine">The owning FSM.</param>
	virtual void Exit_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine);
};
