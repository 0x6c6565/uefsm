// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#include "UEFiniteStateMachineComponent.h"

#include "UEFIniteStateInterface.h"

UUEFiniteStateMachineComponent::UUEFiniteStateMachineComponent()
	: States(), InitialClass(), Current(), TimeInState(0.0), IsPaused(false), AutoLoadComponentStates(true)
{
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(true);
}

void UUEFiniteStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	States.Reset();
	Current.Reset();

	if (AutoLoadComponentStates)
	{
		const AActor* Actor = GetOwner();
		if (nullptr != Actor)
		{
			for (UActorComponent* State : Actor->GetComponentsByInterface(UUEFiniteStateInterface::StaticClass()))
			{
				States.Emplace(State->GetClass(), State);
			}
		}
	}

	if (nullptr != InitialClass.Get())
	{
		Push(InitialClass.Get());
	}

	TimeInState = 0.0;
}

void UUEFiniteStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsPaused)
	{
		Execute(DeltaTime);
	}
}

float UUEFiniteStateMachineComponent::GetTimeInState_Implementation() const
{
	return TimeInState;
}

void UUEFiniteStateMachineComponent::AddStates_Implementation(UPARAM(ref) const TArray<TScriptInterface<IUEFiniteStateInterface>>& Collection)
{
	for (const TScriptInterface<IUEFiniteStateInterface> &State : Collection)
	{
		AddState(State);
	}
}

void UUEFiniteStateMachineComponent::AddState_Implementation(UPARAM(ref) const TScriptInterface<IUEFiniteStateInterface>& State)
{
	if (nullptr != State.GetObject())
	{
		States.Emplace(State.GetObject()->StaticClass(), State.GetObject());
	}
}

void UUEFiniteStateMachineComponent::SetInitialState_Implementation(TSubclassOf<UObject> State)
{
	if (nullptr != State.Get() && States.Contains(State.Get()))
	{
		InitialClass = State.Get();
	}
}

void UUEFiniteStateMachineComponent::Pause_Implementation(bool Value)
{
	if (Value != IsPaused)
	{
		IsPaused = Value;

		// Invoke a delegate here...
	}
}

bool UUEFiniteStateMachineComponent::HasCurrent_Implementation() const
{
	return 0 < Current.Num();
}

bool UUEFiniteStateMachineComponent::IsCurrent_Implementation(TSubclassOf<UObject> State) const
{
	return HasCurrent() && State.Get() == Current.Top().State->GetClass();
}

void UUEFiniteStateMachineComponent::GetCurrent_Implementation(TScriptInterface<IUEFiniteStateInterface>& State, EUEFSMResult& Pins) const
{
	if (TryGetCurrent(State))
	{
		Pins = EUEFSMResult::Valid;
	}
	else
	{
		Pins = EUEFSMResult::Invalid;
	}
}

bool UUEFiniteStateMachineComponent::TryGetCurrent_Implementation(TScriptInterface<IUEFiniteStateInterface>& State) const
{
	if (HasCurrent())
	{
		State = TScriptInterface<IUEFiniteStateInterface>(Current.Top().State);

		return true;
	}

	return false;
}

bool UUEFiniteStateMachineComponent::Contains_Implementation(TSubclassOf<UObject> State) const
{
	return nullptr != State.Get() && State->ImplementsInterface(UUEFiniteStateInterface::StaticClass()) && States.Contains(State.Get());
}

void UUEFiniteStateMachineComponent::Push_Implementation(TSubclassOf<UObject> State)
{
	if (Contains(State) && !IsCurrent(State))
	{
		Current.Push(FUEStateRef(States[State.Get()]));

		Enter();
	}
}

void UUEFiniteStateMachineComponent::Pop_Implementation()
{
	if (HasCurrent())
	{
		Exit();

		Current.Top().Phase = EUEStatePhase::None;

		Current.Pop();
	}
}

void UUEFiniteStateMachineComponent::Change_Implementation(TSubclassOf<UObject> State)
{
	if (Contains(State) && !IsCurrent(State))
	{
		Pop();

		Push(State);
	}
}

bool UUEFiniteStateMachineComponent::HasNoPhase(const FUEStateRef& StateRef) const
{
	return ComparePhase(StateRef, EUEStatePhase::None);
}

bool UUEFiniteStateMachineComponent::HasEntered(const FUEStateRef& StateRef) const
{
	return ComparePhase(StateRef, EUEStatePhase::Entered);
}

bool UUEFiniteStateMachineComponent::HasExecuted(const FUEStateRef& StateRef) const
{
	return ComparePhase(StateRef, EUEStatePhase::Executed);
}

bool UUEFiniteStateMachineComponent::HasEnteredOrExecuted(const FUEStateRef& StateRef) const
{
	return HasEntered(StateRef) || HasExecuted(StateRef);
}

bool UUEFiniteStateMachineComponent::HasExited(const FUEStateRef& StateRef) const
{
	return ComparePhase(StateRef, EUEStatePhase::Exited);
}

bool UUEFiniteStateMachineComponent::ComparePhase(const FUEStateRef& StateRef, const EUEStatePhase& Phase) const
{
	return StateRef.Phase == Phase;
}

void UUEFiniteStateMachineComponent::Enter_Implementation()
{
	if (HasCurrent() && HasNoPhase(Current.Top()))
	{
		TimeInState = 0.0;

		Current.Top().Phase = EUEStatePhase::Entered;

		TScriptInterface<IUEFiniteStateMachineInterface> Machine(this);
		IUEFiniteStateInterface::Execute_Enter(Current.Top().State, Machine);
	}
}

void UUEFiniteStateMachineComponent::Execute_Implementation(float Delta)
{
	if (HasCurrent() && HasEnteredOrExecuted(Current.Top()) && !HasExited(Current.Top()))
	{
		TimeInState += Delta;

		TScriptInterface<IUEFiniteStateMachineInterface> Machine(this);
		if (!HasExecuted(Current.Top()))
		{
			Current.Top().Phase = EUEStatePhase::Executed;
			IUEFiniteStateInterface::Execute_FirstExecute(Current.Top().State, Machine, Delta);
		}
		else
		{
			IUEFiniteStateInterface::Execute_Execute(Current.Top().State, Machine, Delta);
		}
	}
}

void UUEFiniteStateMachineComponent::Exit_Implementation()
{
	if (HasCurrent() && HasEnteredOrExecuted(Current.Top()) && !HasExited(Current.Top()))
	{
		Current.Top().Phase = EUEStatePhase::Exited;

		TScriptInterface<IUEFiniteStateMachineInterface> Machine(this);
		IUEFiniteStateInterface::Execute_Exit(Current.Top().State, Machine);
	}
}
