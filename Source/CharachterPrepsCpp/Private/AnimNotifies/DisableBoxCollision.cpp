// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/DisableBoxCollision.h"
#include "CoolQuinn.h"
#include "Item/Weapon.h"
#include "Components/BoxComponent.h"

void UDisableBoxCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (AnimInstance)
	{
		ACoolQuinn* CoolQuinnActor= Cast<ACoolQuinn>(AnimInstance->TryGetPawnOwner());
		if (CoolQuinnActor)
		{
			if (CoolQuinnActor ->GetEquippedWeapon())
			{
				CoolQuinnActor ->GetEquippedWeapon()-> GetWeaponBox()->
					SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
			
		}
	}
}
