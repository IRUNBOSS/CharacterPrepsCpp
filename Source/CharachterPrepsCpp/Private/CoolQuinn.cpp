// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolQuinn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Item/Item.h"
#include "Item/Weapon.h"


void ACoolQuinn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem
			<UEnhancedInputLocalPlayerSubsystem>(PlayerController -> GetLocalPlayer()))
		{
			Subsystem -> AddMappingContext(CoolQuinnContext,0);
		}
	}
	
}

void ACoolQuinn::AttachWeaponToBack()
{
	if (EquippedWeapon)
	{
		EquippedWeapon -> AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void ACoolQuinn::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon -> AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

void ACoolQuinn::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ACoolQuinn::Move(const FInputActionValue& value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	
	const FVector2d MovementVector = value.Get<FVector2d>();

	const FRotator Rotation = Controller -> GetControlRotation();
	const FRotator YawRotation = FRotator(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
	
}

void ACoolQuinn::Look(const FInputActionValue& value)
{
	const FVector2d LookAxisVector = value.Get<FVector2d>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ACoolQuinn::EKeyPressed(const FInputActionValue& value)
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon-> Equip(GetMesh(), FName("RightHandSocket"),this,this);
		CharacterState = ECharacterState::ECS_EquippedWeapon;
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
	}
	else
	{
		if (CharacterState != ECharacterState::ECS_Unequipped &&
			ActionState == EActionState::EAS_Unoccupied)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance && EquipMontage)
			{
				AnimInstance -> Montage_Play(EquipMontage);
				AnimInstance -> Montage_JumpToSection(FName("WeaponToBack"), EquipMontage);
				
			}
			CharacterState = ECharacterState::ECS_Unequipped;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
		else if (CharacterState == ECharacterState::ECS_Unequipped &&
					ActionState == EActionState::EAS_Unoccupied && EquippedWeapon)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance && EquipMontage)
			{
				AnimInstance -> Montage_Play(EquipMontage);
				AnimInstance -> Montage_JumpToSection(FName("ArmWeapon"), EquipMontage);
				
			}
			CharacterState = ECharacterState::ECS_EquippedWeapon;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
	}
}


void ACoolQuinn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent -> BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACoolQuinn::Move);
		EnhancedInputComponent -> BindAction(LookAction, ETriggerEvent::Triggered, this, &ACoolQuinn::Look);
		EnhancedInputComponent -> BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACoolQuinn::Jump);
		EnhancedInputComponent -> BindAction(EquipAction, ETriggerEvent::Triggered, this, &ACoolQuinn::EKeyPressed);
	}
}


void ACoolQuinn::SetOverlappingItem(AItem* item)
{
	IPickUpInterface::SetOverlappingItem(item);

	OverlappingItem = item;
}