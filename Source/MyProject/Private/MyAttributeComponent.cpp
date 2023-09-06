// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"
#include "MyGMBase.h"

static TAutoConsoleVariable<float> CVarDmgMultier(TEXT("my.DmgMultier"), 1.0f, TEXT("Global attribute comp damage multiplier."), ECVF_Cheat);

// Sets default values for this component's properties
UMyAttributeComponent::UMyAttributeComponent()
{
	HealthMax = 100;
	// ...
}

void UMyAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = HealthMax;
}

bool UMyAttributeComponent::Kill(AActor* Instigator)
{
	return ApplyHealthChange(Instigator, -HealthMax);
}

bool UMyAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float UMyAttributeComponent::ExamHealthRatio() const
{
	return Health / HealthMax;
}

bool UMyAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}
	if (Delta < 0.0f)
	{
		Delta *= CVarDmgMultier.GetValueOnGameThread();
	}
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);
	if (ActualDelta <= 0.0f && Health == 0.0f)
	{
		AMyGMBase* GM = GetWorld()->GetAuthGameMode<AMyGMBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}
	return ActualDelta != 0;
}

UMyAttributeComponent* UMyAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UMyAttributeComponent>(FromActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool UMyAttributeComponent::IsActorAlive(AActor* Actor)
{
	UMyAttributeComponent* AttriComp = GetAttributes(Actor);
	if (AttriComp)
	{
		return AttriComp->IsAlive();
	}
	return false;
}
