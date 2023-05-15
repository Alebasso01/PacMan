// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GridBaseNode.h"
#include "CoreMinimal.h"
#include "PowerNode.generated.h"

UCLASS()
class PACMANGRID_API APowerNode : public AGridBaseNode
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
