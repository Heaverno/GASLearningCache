// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAction.h"
#include <Engine/World.h>

bool UMyAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}
	UActionComponent* Comp = GetOwningComponent();
	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

void UMyAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	UActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRunning = true;
}

void UMyAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopping: %s"), *GetNameSafe(this));
	ensureAlways(bIsRunning);
	UActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(BlockedTags);
	bIsRunning = false;
}

UWorld* UMyAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if (Comp)
	{
		return Comp->GetWorld();
	}
	return nullptr;
}

UActionComponent* UMyAction::GetOwningComponent() const
{
	return Cast<UActionComponent>(GetOuter());
}

bool UMyAction::IsRunning() const
{
	return bIsRunning;
}
