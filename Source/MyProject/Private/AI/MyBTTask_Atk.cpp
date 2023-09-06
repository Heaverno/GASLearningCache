// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTTask_Atk.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAttributeComponent.h"


UMyBTTask_Atk::UMyBTTask_Atk()
{

}

EBTNodeResult::Type UMyBTTask_Atk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyChar = Cast<ACharacter>(MyController->GetPawn());
		if (MyChar == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		FVector MuzzleLoc = MyChar->GetMesh()->GetSocketLocation("Muzzle_Front");
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		if (!UMyAttributeComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation() - MuzzleLoc + FVector{ 0,0,100 };
		FRotator MuzzleRot = Direction.Rotation();
		MuzzleRot.Pitch += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);
		MuzzleRot.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = MyChar;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLoc, MuzzleRot, SpawnParams);
		return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
