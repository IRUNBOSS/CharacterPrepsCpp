// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"

#include "CoolQuinnAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class CHARACHTERPREPSCPP_API UCoolQuinnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	class ACoolQuinn* CoolQuinnActor;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* MovementComponent;
	
	UPROPERTY(BlueprintReadOnly,Category=Movement)
	bool ShouldMove;

	UPROPERTY(BlueprintReadOnly,Category=Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly,Category=Movement)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly,Category=Movement)
	FVector Velocity;
	
	UPROPERTY(BlueprintReadOnly,Category=Movement)
	ECharacterState CharacterState;
	
	
	
};
