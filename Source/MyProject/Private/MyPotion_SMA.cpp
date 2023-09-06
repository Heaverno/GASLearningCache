// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPotion_SMA.h"
#include "MyAttributeComponent.h"

AMyPotion_SMA::AMyPotion_SMA()
{
	RestoreHealth = 80;
	RenableTime = 5;
	bSelfDisabled = false;
}

void AMyPotion_SMA::Interact_Implementation(APawn* InstigatorPawn)
{
	if (InstigatorPawn && !bSelfDisabled)
	{
		UMyAttributeComponent* AttriComp = Cast<UMyAttributeComponent>(InstigatorPawn->GetComponentByClass(UMyAttributeComponent::StaticClass()));
		if (AttriComp)
		{
			if (AttriComp->ExamHealthRatio() < 1.0f)
			{
				AttriComp->ApplyHealthChange(this, RestoreHealth);
				TempSelfDisable();
			}
		}
	}
}

void AMyPotion_SMA::TempSelfDisable()
{
	bSelfDisabled = true;
	GetStaticMeshComponent()->SetScalarParameterValueOnMaterials("Fullness", 0.0f);
	GetWorldTimerManager().SetTimer(TimerHandle_SelfDisabled, this, &AMyPotion_SMA::TempSelfDisable_TimeElapsed, RenableTime);
}

void AMyPotion_SMA::TempSelfDisable_TimeElapsed()
{
	bSelfDisabled = false;
	GetStaticMeshComponent()->SetScalarParameterValueOnMaterials("Fullness", 1.0f);
	TimerHandle_SelfDisabled.Invalidate();
}

