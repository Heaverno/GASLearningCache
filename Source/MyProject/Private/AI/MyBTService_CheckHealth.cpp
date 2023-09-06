// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTService_CheckHealth.h"
#include "MyAttributeComponent.h"
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include "AIController.h"

UMyBTService_CheckHealth::UMyBTService_CheckHealth()
{
	LowHealthFraction = 0.3f;
}

void UMyBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ensure(AIPawn))
	{
		UMyAttributeComponent* AttriComp = UMyAttributeComponent::GetAttributes(AIPawn);
		if (ensure(AttriComp))
		{
			UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
			BlackboardComp->SetValueAsBool(HealthCheckKey.SelectedKeyName, AttriComp->ExamHealthRatio() < LowHealthFraction);
		}
	}
}

