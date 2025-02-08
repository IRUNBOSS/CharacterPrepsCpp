// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"

#include "BaseCharacter.generated.h"

class AWeapon;

UCLASS()
class CHARACHTERPREPSCPP_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint,AActor* Hitter) override;
	void DirectionalHitReact(const FVector& ImpactPoint);
	void PlayHitReactMontage(const FName& SectionName);
	virtual void HandleDamage(float Damage);

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* Attributes;

	UFUNCTION(BLueprintCallable)
	virtual void AttackEnd();
	
	virtual void Attack();
	virtual bool CanAttack();
	virtual int32 PlayAttackMontage();

private:
	UPROPERTY(EditDefaultsOnly, Category=Combat)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category=Combat)
	UAnimMontage* HitReactMontage;

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



