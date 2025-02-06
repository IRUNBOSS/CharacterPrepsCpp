// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Interface/HitInterface.h"


AWeapon::AWeapon()
{
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox ->SetupAttachment(GetRootComponent());
	WeaponBox -> SetCollisionProfileName(FName("Custom"));
	WeaponBox ->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox ->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox ->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart ->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd ->SetupAttachment(GetRootComponent());

	
	
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	AttachMeshToSocket(InParent, InSocketName);
	if (Sphere)
	{
		Sphere -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	
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
	FHitResult BoxHit;
	BoxTrace(BoxHit);

	if (BoxHit.GetActor())
	{
		ExecuteGetHit(BoxHit);
	}
}

void AWeapon::ExecuteGetHit(FHitResult& BoxHit)
{
	IHitInterface* HitInterface = Cast<IHitInterface>(BoxHit.GetActor());
	if (HitInterface)
	{
		HitInterface->Execute_GetHit(BoxHit.GetActor(), BoxHit.ImpactPoint,GetOwner());
	}
}

void AWeapon::BoxTrace(FHitResult& BoxHit)
{
	const FVector Start = BoxTraceStart -> GetComponentLocation();
	const FVector End = BoxTraceEnd -> GetComponentLocation();
	TArray<AActor*> ActorsToIgnore;
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		BoxTraceExtent,
		BoxTraceStart -> GetComponentRotation(),
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		BoxHit,
		true,
		FColor::Red,
		FColor::Green,
		2.f
	);
	
}


