// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
	AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	
	return DamageAmount;
}

void AEnemy::BeginPlay()
{
	InitializeEnemy();
	Super::BeginPlay();
	
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsDead())
	{
		GetController() ->StopMovement();
		return;
	}
		
	
}

void AEnemy::Die_Implementation()
{
	Super::Die_Implementation();
	EnemyState = EEnemyState::EES_Dead;
}

bool AEnemy::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;
	const double DistanceToTarget=(Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget < Radius;
}

void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = ChoosePatrolTarget();
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimerFinished,1.f);
	}
	
}

void AEnemy::PatrolTimerFinished()
{
	MoveToTarget(PatrolTarget);
}

bool AEnemy::IsDead()
{
	return EnemyState==EEnemyState::EES_Dead;
}

AActor* AEnemy::ChoosePatrolTarget()
{
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets)
	{
		if (Target!=PatrolTarget)
		{
			ValidTargets.AddUnique(Target);
		}
	}

	const int32 NumPatrolTargets = ValidTargets.Num();
	if (NumPatrolTargets > 0)
	{
		const int32 TargetSelection=FMath::RandRange(0, NumPatrolTargets-1);
		return ValidTargets[TargetSelection];
	}
	
	return nullptr;
}



void AEnemy::InitializeEnemy()
{
	EnemyController= Cast<AAIController>(GetController());
	MoveToTarget(PatrolTarget);
	
}

void AEnemy::MoveToTarget(AActor* Target)
{
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(100.f);
	EnemyController->MoveTo(MoveRequest);
	
}



