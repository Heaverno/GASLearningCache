// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHoleProjectile.h"

ABlackHoleProjectile::ABlackHoleProjectile()
{
	ProjectileMovementComp->InitialSpeed = 2000.0f;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 5120;
	RadialForceComp->ImpulseStrength = -299999;
	RadialForceComp->bIgnoreOwningActor = 1;
	//TArray<EObjectTypeQuery> ObjectTypesToAffect;
	//RadialForceComp->AddObjectTypeToAffect(TEnumAsByte<EObjectTypeQuery> ObjectTypesToAffect);
}

void ABlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	//RadialForceComp->FireImpulse();
}

void ABlackHoleProjectile::ProjectileExplode_Implementation()
{
	;
}
