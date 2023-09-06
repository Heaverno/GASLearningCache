// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 40));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->TargetArmLength = 210;
	SpringArmComp->SocketOffset = FVector(0, 55, 0);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	InteractComp = CreateDefaultSubobject<UMyInteractComponent>("InteractComp");
	AttriComp = CreateDefaultSubobject<UMyAttributeComponent>("AttriComp");
	ActionComp = CreateDefaultSubobject<UActionComponent>("ActionComp");

	HitColor = FLinearColor::White;
	FlashSpeed = 4.6f;
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttriComp->OnHealthChanged.AddDynamic(this, &AMyCharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetScalarParameterValueOnMaterials("FlashSpeed", FlashSpeed);
	GetMesh()->SetVectorParameterValueOnMaterials("HitColor", UKismetMathLibrary::Conv_LinearColorToVector(HitColor));
}

void AMyCharacter::FMoveFwd(float val)
{
	FRotator CtrlRot = GetControlRotation();
	CtrlRot.Pitch = 0; CtrlRot.Roll = 0;
	AddMovementInput(CtrlRot.Vector(), val);
}

void AMyCharacter::FMoveRt(float val)
{
	FRotator CtrlRot = GetControlRotation(); //FRotator(GetControlRotation().Yaw, 0.0f, 0.0f);
	CtrlRot.Pitch = 0; CtrlRot.Roll = 0;
	FVector VectorRt = FRotationMatrix(CtrlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(VectorRt, val);
}

void AMyCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void AMyCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

void AMyCharacter::PrimaryAtk()
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}

void AMyCharacter::SkillQ()
{
	ActionComp->StartActionByName(this, "SkillQ");
}

void AMyCharacter::SkillR()
{
	ActionComp->StartActionByName(this, "SkillR");
}

void AMyCharacter::PrimaryInteract()
{
	InteractComp->PrimaryInteract();
}

void AMyCharacter::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
		if (NewHealth <= 0.0f)
		{
			APlayerController* PC = Cast<APlayerController>(GetController());
			DisableInput(PC);
		}
	}
}

void AMyCharacter::HealSelf(float Amount /* = 100 */)
{
	AttriComp->ApplyHealthChange(this, Amount);
}

FVector AMyCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveFwd", this, &AMyCharacter::FMoveFwd);
	PlayerInputComponent->BindAxis("MoveRt", this, &AMyCharacter::FMoveRt);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::SprintStop);
	PlayerInputComponent->BindAction("PrimaryAtk", IE_Pressed, this, &AMyCharacter::PrimaryAtk);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMyCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
	PlayerInputComponent->BindAction("SkillQ", IE_Pressed, this, &AMyCharacter::SkillQ);
	PlayerInputComponent->BindAction("SkillR", IE_Pressed, this, &AMyCharacter::SkillR);
}

