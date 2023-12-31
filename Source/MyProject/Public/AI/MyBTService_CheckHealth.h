// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_CheckHealth.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyBTService_CheckHealth : public UBTService
{
	GENERATED_BODY()
	
public:
	UMyBTService_CheckHealth();

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	float LowHealthFraction;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector HealthCheckKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
