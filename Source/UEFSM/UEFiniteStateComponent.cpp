// Fill out your copyright notice in the Description page of Project Settings.

#include "UEFiniteStateComponent.h"

#include "UEFiniteStateMachineInterface.h"

UUEFiniteStateComponent::UUEFiniteStateComponent()
	: Phase(EUEStatePhase::None)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetComponentTickEnabled(false);
}


void UUEFiniteStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UUEFiniteStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
