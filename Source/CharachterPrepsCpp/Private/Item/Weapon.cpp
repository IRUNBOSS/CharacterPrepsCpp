// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon.h"
#include "Components/BoxComponent.h"


AWeapon::AWeapon()
{
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox ->SetupAttachment(GetRootComponent());
	WeaponBox -> SetCollisionProfileName(FName("Custom"));
	WeaponBox ->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox ->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox ->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
		
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	AttachMeshToSocket(InParent, InSocketName);
	
	
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,true);
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponBox ->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Blue,TEXT("OnBoxOverlap"));
}
