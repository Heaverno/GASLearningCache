// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"
#include "MyAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyBlueprintFunctionLibrary.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMyProjectile::OnActorOverlap);
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComp");
	NiagaraComp->SetupAttachment(SphereComp);
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 4000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = 1;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = 1;
	Damage = 20.0f;
}

void AMyProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
// 		UMyAttributeComponent* AttriComp = Cast<UMyAttributeComponent>(OtherActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));
// 		if (AttriComp)
// 		{
// 			AttriComp->ApplyHealthChange(GetInstigator(), -Damage);
// 		}
// 		ProjectileExplode();
		if (UMyBlueprintFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, SweepResult))
		{
			ProjectileExplode();
		}
	}
}

void AMyProjectile::ProjectileExplode_Implementation()
{
	if (ensure(IsValid(this)))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}

// Called when the game starts or when spawned
void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
void AMyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

