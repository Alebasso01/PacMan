// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhantomPawn.h"
#include "PacmanPawn.h"
#include "Clyde.generated.h"

/**
 *
 */
UCLASS()
class PACMANGRID_API AClyde : public APhantomPawn
{
	GENERATED_BODY()
		virtual AGridBaseNode* GetPlayerRelativeTarget() override;

public:
	AClyde();
	virtual void Tick(float DeltaTime) override;
	void SetGhostTarget();
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EGhostId> EGhostId = Clyde;
	void TeleportClyde();
};
