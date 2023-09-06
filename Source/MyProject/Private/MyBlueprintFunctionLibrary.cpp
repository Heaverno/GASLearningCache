// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "MyAttributeComponent.h"

bool UMyBlueprintFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UMyAttributeComponent* AttriComp = UMyAttributeComponent::GetAttributes(TargetActor);
	if (AttriComp)
	{
		return AttriComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}
	return false;
}

bool UMyBlueprintFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(HitResult.ImpactNormal * -30000.0f, HitResult.ImpactPoint, HitResult.BoneName);
			return true;
		}
	}
	return false;
}
