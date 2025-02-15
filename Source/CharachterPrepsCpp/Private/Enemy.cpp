// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Item/Weapon.h"
#include "Perception/PawnSensingComponent.h"
#include  "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy()
{
	ResetOwnedComponents();

	ShieldComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	ShieldComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UStaticMesh* ShieldMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Megascans/3D_Assets/Wooden_Wheel_ugrfefpfa/S_Wooden_Wheel_ugrfefpfa_lod3_Var1"));
	if (ShieldMesh)
		ShieldComponent -> SetStaticMesh(ShieldMesh);
	const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ShieldComponent -> AttachToComponent(GetMesh(), TransformRules, FName("ShieldSocket"));

	PawnSensing=CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing ->SightRadius=6000;
	PawnSensing -> SetPeripheralVisionAngle(60.f);
	
}

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
                         AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	
	return DamageAmount;
}

void AEnemy::BeginPlay()
{
	if (PawnSensing) PawnSensing -> OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
	InitializeEnemy();
	Super::BeginPlay();
	
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsDead())
	{
		GetController() -> StopMovement();
		return;
	}
	if (EnemyState > EEnemyState::EES_Patrolling)
	{
		CheckCombatTarget();
	}
	else
	{
		CheckPatrolTarget();
	}
	
}

void AEnemy::Die_Implementation()
{
	Super::Die_Implementation();
	EnemyState = EEnemyState::EES_Dead;
	DisableCapsule();
	DisableMeshCollision();
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

void AEnemy::SpawnDefaultWeapon()
{
	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		AWeapon* DefaultWeapon = World ->SpawnActor<AWeapon>(WeaponClass);
		DefaultWeapon -> Equip(GetMesh(), FName("WeaponSocket"),this,this);
		EquippedWeapon= DefaultWeapon;
	}

	
}

void AEnemy::ClearPatrolTimer()
{
	GetWorldTimerManager().ClearTimer(PatrolTimer);
}

void AEnemy::ChaseTarget()
{
	EnemyState = EEnemyState::EES_Chasing;
	GetCharacterMovement() -> MaxWalkSpeed = ChasingSpeed;
	MoveToTarget(CombatTarget);
}

void AEnemy::StartPatrolling()
{
	EnemyState = EEnemyState::EES_Patrolling;
	GetCharacterMovement() -> MaxWalkSpeed = PatrollingSpeed;
	MoveToTarget(PatrolTarget);
}

void AEnemy::CheckCombatTarget()
{
	if (IsOutsideCombatRadius())
	{
		LoseInterest();
		StartPatrolling();
	}
	else
	{
		ChaseTarget();
	}
}

bool AEnemy::IsOutsideCombatRadius()
{
	return !InTargetRange(CombatTarget, CombatRadius);
}

bool AEnemy::IsInsideCombatRadius()
{
	return InTargetRange(CombatTarget, CombatRadius);
}

void AEnemy::LoseInterest()
{
	CombatTarget = nullptr;
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
	SpawnDefaultWeapon();
	
}

void AEnemy::MoveToTarget(AActor* Target)
{
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(100.f);
	EnemyController->MoveTo(MoveRequest);
	
}

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	const bool bShouldChaseTarget=
		SeenPawn -> ActorHasTag(FName("EngageableTarget"));

	if (bShouldChaseTarget)
	{
		CombatTarget = SeenPawn;
		if (IsInsideCombatRadius())
		{
			ClearPatrolTimer();
			ChaseTarget();
		}
	}
}


