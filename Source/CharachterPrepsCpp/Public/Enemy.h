// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class CHARACHTERPREPSCPP_API AEnemy : public ABaseCharacter
{
	
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	
	class AAIController* EnemyController;
	void InitializeEnemy();
	void MoveToTarget(AActor* Target);
	bool InTargetRange(AActor* Target, double Radius);
	void CheckPatrolTarget();
	AActor* ChoosePatrolTarget();
	FTimerHandle PatrolTimer;
	void PatrolTimerFinished();

	UPROPERTY(EditAnywhere)
	double PatrolRadius =200.f;
	
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TArray<AActor*> PatrolTargets;
	
};
