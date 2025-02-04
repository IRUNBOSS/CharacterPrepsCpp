// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
#include "Interface/PickUpInterface.h"
#include "CharacterTypes.h"

#include "CoolQuinn.generated.h"

class UInputAction;
class UInputEvent;
class AItem;
class UAnimMontage;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class CHARACHTERPREPSCPP_API ACoolQuinn : public ABaseCharacter, public IPickUpInterface
{
	GENERATED_BODY()
public:
	virtual void SetOverlappingItem(AItem* item) override;
	
private:

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	UPROPERTY()
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY()
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
protected:
	virtual void BeginPlay() override;
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;

	void Disarm();
	bool CanDisarm();
	void Arm();
	bool CanArm();
	void PlayEquipMantage(const FName& SectionName);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* CoolQuinnContext;

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void EKeyPressed(const FInputActionValue& value);
	
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};


