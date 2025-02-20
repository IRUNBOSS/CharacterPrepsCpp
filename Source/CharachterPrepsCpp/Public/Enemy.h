// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"

#include "Enemy.generated.h"

class UPawnSensingComponent;

/**
 * 
 */
UCLASS()
class CHARACHTERPREPSCPP_API AEnemy : public ABaseCharacter
{
	
	GENERATED_BODY()

public:
	AEnemy();
	virtual float TakeDamage(float DamageAmount,  
	struct FDamageEvent const & DamageEvent,  
	class AController * EventInstigator,  
	AActor * DamageCauser)override; 
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Die_Implementation() override;
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint,AActor* Hitter) override;


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

private:
	class AAIController* EnemyController;

	void InitializeEnemy();
	void MoveToTarget(AActor* Target);
	bool InTargetRange(AActor* Target, double Radius);
	void CheckPatrolTarget();
	AActor* ChoosePatrolTarget();
	FTimerHandle PatrolTimer;
	FTimerHandle AttackTimer;
	void PatrolTimerFinished();
	bool IsDead();
	void SpawnDefaultWeapon();
	void ClearPatrolTimer();
	void ChaseTarget();
	void StartPatrolling();
	void CheckCombatTarget();
	bool IsOutsideCombatRadius();
	bool IsInsideCombatRadius();
	void LoseInterest();
	bool IsOutSideAttackRadius();
	bool IsEngaged();
	bool IsAttacking();
	void StartAttackTimer();
	void ClearAttackTimer();

	UPROPERTY(EditAnywhere)
	double PatrolRadius =200.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius =500.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRadius =200.f;
	
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere, Category= Combat)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category= Combat)
	UStaticMeshComponent* ShieldComponent;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, category=Combat)
	float PatrollingSpeed =125.f;

	UPROPERTY(EditAnywhere, category=Combat)
	float ChasingSpeed =300.f;

	UPROPERTY(EditAnywhere, category=Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, category=Combat)
	float AttackMax = 1.f;
	
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);
	
};
