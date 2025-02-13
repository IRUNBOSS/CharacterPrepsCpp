// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"

#include "Enemy.generated.h"

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
	void PatrolTimerFinished();
	bool IsDead();
	void SpawnDefaultWeapon();

	UPROPERTY(EditAnywhere)
	double PatrolRadius =200.f;
	
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere, Category= Combat)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category= Combat)
	UStaticMeshComponent* ShieldComponent;
	
};
