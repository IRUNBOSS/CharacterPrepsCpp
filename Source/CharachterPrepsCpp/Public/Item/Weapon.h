// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"

#include "Weapon.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class CHARACHTERPREPSCPP_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();
	void Equip(USceneComponent* InParent,FName InSocketName, AActor* NewOwner, APawn* NewInstigator);
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
	TArray<AActor*> IgnoreActors;

protected:
	virtual void BeginPlay() override;
	void ExecuteGetHit(FHitResult& BoxHit);

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
private:
	void BoxTrace(FHitResult& BoxHit);

	UPROPERTY(EditAnywhere, Category="Weapon Properties")
	FVector BoxTraceExtent = FVector(5.0f);
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon Properties")
	UBoxComponent* WeaponBox;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;


public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const {return WeaponBox;}
	
};
