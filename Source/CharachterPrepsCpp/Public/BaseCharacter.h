// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "CharacterTypes.h"

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
	virtual int32 PlayDeathMontage();
	virtual void HandleDamage(float Damage);
	void StopAttackMontage();

	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;

	UPROPERTY(BlueprintReadWrite, Category=Combat);
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double WarpTargetDistance = 75.f;

	UPROPERTY(EditAnywhere, Category=Combat)
	UParticleSystem* HitParticles;
	
	UFUNCTION(BLueprintCallable)
	virtual void AttackEnd();

	UFUNCTION(BLueprintCallable)
	FVector GetTranslationWarpTarget();

	UFUNCTION(BLueprintCallable)
	FVector GetRotationWarpTarget();
	
	UFUNCTION(BlueprintNativeEvent)
	void Die();
	
	virtual void Attack();
	virtual bool CanAttack();
	virtual int32 PlayAttackMontage();
	void DisableCapsule();
	void DisableMeshCollision();
	void SpawnHitParticles(const FVector& ImpactPoint);

private:
	UPROPERTY(EditDefaultsOnly, Category=Combat)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category=Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category=Combat)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category=Combat)
	TArray<FName> AttackMontageSections;

	UPROPERTY(EditAnywhere, Category=Combat)
	TArray<FName> DeathMontageSections;

	int32 PlayRandomMontageSection(UAnimMontage* AnimMontage, const TArray<FName>& SectionNames);
	void PlayMontageSection(UAnimMontage* AnimMontage, const FName& SectionName);
	bool IsAlive();

	

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE AWeapon* GetEquippedWeapon() const {return EquippedWeapon; }
	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const { return DeathPose; }
	
};



