// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "BlackHoleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ABlackHoleProjectile : public AMyProjectile
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* RadialForceComp;

	virtual void BeginPlay() override;
	virtual void ProjectileExplode_Implementation() override;

public:
	ABlackHoleProjectile();
};
