// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickUpInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPickUpInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARACHTERPREPSCPP_API IPickUpInterface
{
	GENERATED_BODY()

public:
	virtual void SetOverlappingItem(class AItem* item);
	
};
