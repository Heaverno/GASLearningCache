// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTarget.h"

// Sets default values
AMyTarget::AMyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetSimulatePhysics(1);
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 5120;
	RadialForceComp->ImpulseStrength = 1299999;
	RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Linear;
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	AttriComp = CreateDefaultSubobject<UMyAttributeComponent>("AttriComp");
	AttriComp->OnHealthChanged.AddDynamic(this, &AMyTarget::OnHealthChanged);
}

void AMyTarget::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AMyTarget::OnActorHit);
}

// Called when the game starts or when spawned
void AMyTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyTarget::OnActorHit(UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TriggerFireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in MyTarget"));
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	FString CombineString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombineString, nullptr, FColor::Cyan, 2.0f, true);
}

void AMyTarget::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		StaticMeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

void AMyTarget::TriggerFireImpulse()
{
	RadialForceComp->FireImpulse();
}

// Called every frame
void AMyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
