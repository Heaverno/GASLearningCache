// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractComponent.h"
#include "MyGameplayInterface.h"

static TAutoConsoleVariable<bool> CVarDrawInteractionDebug(TEXT("my.DrawInteractionDebug"), false, TEXT("Enable Debug lines for Interaction."), ECVF_Cheat);

// Sets default values for this component's properties
UMyInteractComponent::UMyInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMyInteractComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//FVector Start = GetOwner()->GetActorLocation();
	FVector EyeLoc; FRotator EyeRot;
	GetOwner()->GetActorEyesViewPoint(EyeLoc, EyeRot);
	FVector End = EyeLoc + (EyeRot.Vector() * 1000);
	//FHitResult Hit;
	//GetWorld()->LineTraceSingleByObjectType(Hit, EyeLoc, End, QueryParams);

	TArray<FHitResult> Hits;
	float SphereRadius = 64;
	FCollisionShape Shape;
	Shape.SetSphere(SphereRadius);
	bool bHitBlocked = GetWorld()->SweepMultiByObjectType(Hits, EyeLoc, End, FQuat::Identity, QueryParams, Shape);
	FColor DebugLineColor = bHitBlocked ? FColor::Green : FColor::Magenta;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UMyGameplayInterface>())
			{
				IMyGameplayInterface::Execute_Interact(HitActor, Cast<APawn>(GetOwner()));  
			}
		}
		if (CVarDrawInteractionDebug.GetValueOnGameThread())
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, SphereRadius, 16, DebugLineColor, 0, 0.6f, 0u, 0.5f);
		}
		break;
	}
	if (CVarDrawInteractionDebug.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), EyeLoc, End, DebugLineColor, false, 0.6f, 0U, 0.5f);
	}
}