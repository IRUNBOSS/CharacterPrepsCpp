// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

