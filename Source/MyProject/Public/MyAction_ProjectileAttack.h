// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAction.h"
#include "MyAction_ProjectileAttack.generated.h"

class UAnimMontage;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyAction_ProjectileAttack : public UMyAction
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UNiagaraSystem* CastingEffect;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);
	
public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	UMyAction_ProjectileAttack();
};
