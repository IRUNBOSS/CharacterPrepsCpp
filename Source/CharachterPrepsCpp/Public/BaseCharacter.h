// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Item/Weapon.h"

#include "BaseCharacter.generated.h"

UCLASS()
class CHARACHTERPREPSCPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	UFUNCTION(BLueprintCallable)
	virtual void AttackEnd();
	
	virtual void Attack();
	virtual bool CanAttack();
	virtual int32 PlayAttackMontage();

private:
	UPROPERTY(EditDefaultsOnly, Category=Combat)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category=Combat)
	TArray<FName> AttackMontageSections;

	int32 PlayRandomMontageSection(UAnimMontage* AnimMontage, const TArray<FName>& SectionNames);
	void PlayMontageSection(UAnimMontage* AnimMontage, const FName& SectionName);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};


