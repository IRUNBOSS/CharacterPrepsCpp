#pragma once

UENUM(BlueprintType)

enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedWeapon UMETA(DisplayName = "EquippedWeapon"),
	ECS_WeaponBack UMETA(DisplayName = "WeaponBack")
	
};

UENUM(BlueprintType)

enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_EquippingWeapon UMETA(DisplayName = "EquippingWeapon"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_Dead UMETA(DisplayName = "Dead")
	
};

UENUM(BlueprintType)

enum class EEnemyState : uint8
{
	EES_NoState UMETA(DisplayName = "NoState"),
	
	EES_Dead UMETA(DisplayName = "Dead"),
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged")
	
};

UENUM(BlueprintType)

enum EDeathPose
{
	EDP_DeadFront UMETA(DisplayName = "DeadFront"),
	EDP_DeadBack UMETA(DisplayName = "DeadBack"),
	EDP_DeadRight UMETA(DisplayName = "DeadRight"),
	
	EDP_MAX UMETA(DisplayName = "DeadMAX")
	
};
