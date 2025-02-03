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
	EAS_EquippingWeapon UMETA(DisplayName = "EquippingWeapon")
	
};