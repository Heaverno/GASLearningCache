// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include "UI/MyGameWorldWidget.h"
#include "Components/CapsuleComponent.h"
#include <GameFramework/CharacterMovementComponent.h>


AMyAICharacter::AMyAICharacter()
{
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensor");
	AttriComp = CreateDefaultSubobject<UMyAttributeComponent>("AttriComp");
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	TimeToHitParamName = "TimeToHitParamName";
}

void AMyAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensor->OnSeePawn.AddDynamic(this, &AMyAICharacter::OnPawnSeen);
	AttriComp->OnHealthChanged.AddDynamic(this, &AMyAICharacter::OnHealthChanged);
}

void AMyAICharacter::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}
		if (!ActiveHealthBar)
		{
			ActiveHealthBar = CreateWidget<UMyGameWorldWidget>(GetWorld(), HealthBarWidgetClass);
		}
		if (ActiveHealthBar)
		{
			ActiveHealthBar->AttachedActor = this;
			ActiveHealthBar->AddToViewport();
		}
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
		if (NewHealth <= 0.0f)
		{
			//AI death, stop BT, ragdoll, set lifespan
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			GetCharacterMovement()->DisableMovement(); 
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			SetLifeSpan(10.0f);
		}
	}
}

void AMyAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}

void AMyAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}
