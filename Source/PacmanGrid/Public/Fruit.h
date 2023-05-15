// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GridBaseNode.h>
#include "Fruit.generated.h"

UCLASS()
class PACMANGRID_API AFruit : public AGridBaseNode
{
	GENERATED_BODY()

public:	
	AFruit();

protected:
	virtual void BeginPlay() override;

public:
	FTimerHandle Timer;
	void SetVisibilityOn();
};