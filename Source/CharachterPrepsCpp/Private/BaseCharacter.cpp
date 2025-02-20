// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/AttributeComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	if (IsAlive()&&Hitter)
	{
		DirectionalHitReact(Hitter->GetActorLocation());
	}
	else
	{
		Die();
	}
}

void ABaseCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	const FVector Impact_L(ImpactPoint.X,ImpactPoint.Y,GetActorLocation().Z);
	const FVector ToHit = (Impact_L - GetActorLocation()).GetSafeNormal();
	const double CosTheta =FVector::DotProduct(Forward,ToHit);
	double Theta = FMath::Acos(CosTheta);
	Theta = FMath::RadiansToDegrees(Theta);

	const FVector CrossProduct = FVector::CrossProduct(Forward,ToHit);

	if (CrossProduct.Z < 0)
		Theta *= -1.f;
	

	FName Section("FromBack");
	
	if (Theta >=-45.f && Theta < 45.f)
		Section = "FromFront";
	else if (Theta > -135.f && Theta < -45.f)
		Section = "FromLeft";
	else if ( Theta > 45.f && Theta < 135.f)
		Section = "FromRight";

	PlayHitReactMontage(Section);
}

void ABaseCharacter::PlayHitReactMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage)
	{
		AnimInstance -> Montage_Play(HitReactMontage);
		AnimInstance-> Montage_JumpToSection(SectionName, HitReactMontage);
	}
}

int32 ABaseCharacter::PlayDeathMontage()
{
	const int32 Selection = PlayRandomMontageSection(DeathMontage,DeathMontageSections);
	TEnumAsByte<EDeathPose> Pose(Selection);
	if (Pose< EDeathPose::EDP_MAX)
		DeathPose = Pose;
	
	return Selection;
}

void ABaseCharacter::HandleDamage(float Damage)
{
	if (Attributes)
	{
		Attributes -> ReceiveDamage(Damage);
	}
}

void ABaseCharacter::StopAttackMontage()
{
	UAnimInstance* AnimInsatance = GetMesh() -> GetAnimInstance();
	if (AnimInsatance)
	{
		AnimInsatance ->Montage_Stop(0.25f, AttackMontage);
	}
}

void ABaseCharacter::AttackEnd()
{
	
}

void ABaseCharacter::Attack()
{
	
}

bool ABaseCharacter::CanAttack()
{
	
	return false;
}

int32 ABaseCharacter::PlayAttackMontage()
{
	
	return PlayRandomMontageSection(AttackMontage, AttackMontageSections);
}

void ABaseCharacter::DisableCapsule()
{
	GetCapsuleComponent() ->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseCharacter::DisableMeshCollision()
{
	GetMesh() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

inline int32 ABaseCharacter::PlayRandomMontageSection(UAnimMontage* AnimMontage, const TArray<FName>& SectionNames)
{
	if (SectionNames.Num()<=0) return -1;

	const int32 MaxSectionIndex = SectionNames.Num() - 1;
	const int32 Selection = FMath::RandRange(0, MaxSectionIndex);
	PlayMontageSection(AnimMontage,SectionNames[Selection]);
	return Selection;
}

void ABaseCharacter::PlayMontageSection(UAnimMontage* AnimMontage, const FName& SectionName)
{
	UAnimInstance* AnimInsatance = GetMesh() -> GetAnimInstance();
	if (AnimInsatance && AnimMontage)
	{
		AnimInsatance -> Montage_Play(AnimMontage);
		AnimInsatance ->Montage_JumpToSection(SectionName,AnimMontage);
	}
}

bool ABaseCharacter::IsAlive()
{
	return Attributes && Attributes -> IsAlive();
}

void ABaseCharacter::Die_Implementation()
{

	PlayDeathMontage();
	
}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

