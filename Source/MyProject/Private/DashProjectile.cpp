// Fill out your copyright notice in the Description page of Project Settings.


#include "DashProjectile.h"

ADashProjectile::ADashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	ProjectileMovementComp->InitialSpeed = 6000.0f;
}

void ADashProjectile::ProjectileExplode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	if (ensure(IsValid(this)))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactFX, GetActorLocation(), GetActorRotation());
		NiagaraComp->Deactivate();
		ProjectileMovementComp->StopMovementImmediately();
		SetActorEnableCollision(false);
		FTimerHandle TimerHandle_DelayedTeleport;
		GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ADashProjectile::TeleportInstigator, TeleportDelay);
	}
}

void ADashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation()+FVector{0,0,90}, ActorToTeleport->GetActorRotation());
	}
}

void ADashProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ADashProjectile::ProjectileExplode, DetonateDelay);
}

