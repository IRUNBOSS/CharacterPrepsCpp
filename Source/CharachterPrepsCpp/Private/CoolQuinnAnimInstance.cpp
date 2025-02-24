// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolQuinnAnimInstance.h"
#include "CoolQuinn.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCoolQuinnAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CoolQuinnActor = Cast <ACoolQuinn>(TryGetPawnOwner());
	if (CoolQuinnActor != nullptr)
	{
		MovementComponent = CoolQuinnActor->GetCharacterMovement();
	}
}

void UCoolQuinnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent != nullptr)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		IsFalling = MovementComponent->IsFalling();
		Velocity=MovementComponent->Velocity;
		ShouldMove = GroundSpeed >3.f &&
			UKismetMathLibrary::VSizeXY(MovementComponent->GetCurrentAcceleration()) != 0;

		CharacterState= CoolQuinnActor->GetCharacterState();
		ActionState = CoolQuinnActor->GetActionState();
		DeathPose = CoolQuinnActor->GetDeathPose();
	}
	
}
