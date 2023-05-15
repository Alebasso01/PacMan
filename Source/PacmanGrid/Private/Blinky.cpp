// Fill out your copyright notice in the Description page of Project Settings.


#include "Blinky.h"

AGridBaseNode* ABlinky::GetPlayerRelativeTarget()
{
	return Super::GetPlayerRelativeTarget();
}

ABlinky::ABlinky()
{
	EGhostId = Blinky;
}

void ABlinky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->GetTargetNode() == nullptr)
	{
		SetGhostTarget();
	}
}

void ABlinky::SetGhostTarget()
{
	const AGridBaseNode* Target = GetPlayerRelativeTarget();
	if (chase == true && frightned == false && scatter == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(16, 13))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 13)));
		}
		else
		{
			Target = GetPlayer()->GetLastNode();
		}
	}
	else if (scatter == true && chase == false && frightned == false && eaten == false)
	{
		
		if (LastNode->GetGridPosition() == FVector2D(16, 13))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 13)));
		}
		else
		{
			Target = *(TeleportNode.Find(FVector2D(29, 22)));
		}
	}
	else if (frightned == true && chase == false && scatter == false && eaten == false)
	{
		FVector2D newTarget = Super::RandomMovement();
		Target = *(TeleportNode.Find(newTarget));
	}
	else if (eaten == true && frightned == false && chase == false && scatter == false)
	{
		CurrentMovementSpeed = 1000.0f;
		Target = *(TeleportNode.Find(FVector2D(20, 13)));
		if (LastNode->GetGridPosition() == FVector2D(20, 13))
		{
			SetNextNode(*(TeleportNode.Find(FVector2D(16, 13))));
			SetTargetNode(NextNode);
			LastNode = *(TeleportNode.Find(FVector2D(16, 13)));
			const FVector Inside(1650.0f, 1350.0f, GetActorLocation().Z);
			SetActorLocation(Inside);
			ResetMesh();
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::TeleportOutside, 0.5, true);
		}
	}
	AGridBaseNode* PossibleNode = TheGridGen->GetClosestNodeFromMyCoordsToTargetCoords(this->GetLastNodeCoords(), Target->GetGridPosition(), -(this->GetLastValidDirection()));

	const FVector Dimensions(60, 60, 20);
	DrawDebugBox(GetWorld(), PossibleNode->GetTileCoordinates(), Dimensions, FColor::Red);

	if (PossibleNode)
	{
		this->SetNextNodeByDir(TheGridGen->GetThreeDOfTwoDVector(PossibleNode->GetGridPosition() - this->GetLastNodeCoords()), true);
	}
}
void ABlinky::TeleportBlinky()
{
	SetNextNode(*(TeleportNode.Find(FVector2D(20, 13))));
	SetTargetNode(NextNode);
	LastNode = *(TeleportNode.Find(FVector2D(18, 13)));
	const FVector Inside(1850.0f, 1350.0f, GetActorLocation().Z);
	SetActorLocation(Inside);
}

