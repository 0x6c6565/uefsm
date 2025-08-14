// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

#include "UEFiniteStateComponent.h"

#include "UEFiniteStateMachineInterface.h"

UUEFiniteStateComponent::UUEFiniteStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetComponentTickEnabled(false);
}

// This really doesn't need to be here.
void UUEFiniteStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

// This really doesn't need to be here.
void UUEFiniteStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUEFiniteStateComponent::Enter_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine)
{
}

void UUEFiniteStateComponent::FirstExecute_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta)
{
}

void UUEFiniteStateComponent::Execute_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine, float Delta)
{
}

void UUEFiniteStateComponent::Exit_Implementation(UPARAM(ref) const TScriptInterface<class IUEFiniteStateMachineInterface>& Machine)
{
}
