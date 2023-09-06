// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAction_ProjectileAttack.h"
#include <GameFramework/Character.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>

UMyAction_ProjectileAttack::UMyAction_ProjectileAttack()
{
	AttackAnimDelay = 0.2f;
	HandSocketName = "Muzzle_01";
}

void UMyAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("qwq!"));
	if (ensureAlways(ProjectileClass))
	{
		FVector HandLoc = InstigatorCharacter->GetMesh()->GetSocketLocation("Muzzle_01");
		FActorSpawnParameters SpawnParams; 
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;
		FHitResult Hit; 
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);
		FCollisionQueryParams QueryParams; 
		QueryParams.AddIgnoredActor(InstigatorCharacter);
		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();
		FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000);
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, QueryParams))
		{
			//SpawnTM = FTransform((Hit.ImpactPoint - HandLoc).Rotation(), HandLoc);
			TraceEnd = Hit.ImpactPoint;
		}
		else
		{
			//FRotator qwq = FRotationMatrix::MakeFromXY()
			//SpawnTM = FTransform((Hit.TraceEnd - HandLoc).Rotation(), HandLoc);
		}
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLoc).Rotator();
		FTransform SpawnTM = FTransform(ProjRotation, HandLoc);
		UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, InstigatorCharacter->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
	StopAction(InstigatorCharacter);
}

void UMyAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);
		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}
}
