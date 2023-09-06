// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MyGameplayInterface.h"
#include "MyPotion_SMA.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPotion_SMA : public AStaticMeshActor, public IMyGameplayInterface
{
	GENERATED_BODY()
	
protected:
	void Interact_Implementation(APawn* InstigatorPawn);

	UPROPERTY(EditDefaultsOnly)
	float RestoreHealth;
	UPROPERTY(EditDefaultsOnly)
	float RenableTime;

	bool bSelfDisabled;
	FTimerHandle TimerHandle_SelfDisabled;

	void TempSelfDisable();
	void TempSelfDisable_TimeElapsed();

public:
	AMyPotion_SMA();

};
