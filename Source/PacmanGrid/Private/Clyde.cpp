// Fill out your copyright notice in the Description page of Project Settings.


#include "Clyde.h"

AGridBaseNode* AClyde::GetPlayerRelativeTarget()
{
	return Super::GetPlayerRelativeTarget();
}

AClyde::AClyde()
{
	EGhostId = Clyde;
}

void AClyde::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->GetTargetNode() == nullptr)
	{
		SetGhostTarget();
	}
}

void AClyde::SetGhostTarget()
{
	const AGridBaseNode* Target = GetPlayerRelativeTarget();
	
	if (chase == true && frightned == false && scatter == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 16))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(16, 16)));
		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 16))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 16)));
		}
		else
		{
			FVector2D Distance;
			Distance.X = GetPlayer()->GetLastNodeCoords().X - this->GetLastNodeCoords().X;
			Distance.Y = GetPlayer()->GetLastNodeCoords().Y - this->GetLastNodeCoords().Y;
			int distance = Distance.Size();
			if (distance < 15)
			{
				Target = *(TeleportNode.Find(FVector2D(11, 13)));
			}
			else
			{
				Target = GetPlayer()->GetLastNode();
			}
		}
	}
	else if (scatter == true && chase == false && frightned == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 16))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(16, 16)));

		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 16))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 16)));
		}
		else
		{
			Target = *(TeleportNode.Find(FVector2D(2, 11)));
		}
		
	}
	else if (frightned == true && chase == false && scatter == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 16))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(16, 16)));

		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 16))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 16)));
		}
		else {
			FVector2D newTarget = Super::RandomMovement();
			Target = *(TeleportNode.Find(newTarget));
		}
	}
	else if (eaten == true && frightned == false && chase == false && scatter == false)
	{
		CurrentMovementSpeed = 1000.0f;
		Target = *(TeleportNode.Find(FVector2D(20, 13)));
		if (LastNode->GetGridPosition() == FVector2D(20, 13))
		{
			TeleportClyde();
			ResetMesh();
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::TeleportOutside, 5, true);
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
void AClyde::TeleportClyde()
{
	SetNextNode(*(TeleportNode.Find(FVector2D(18, 16))));
	SetTargetNode(NextNode);
	LastNode = *(TeleportNode.Find(FVector2D(18, 16)));
	const FVector Inside(1850.0f, 1650.0f, GetActorLocation().Z);
	SetActorLocation(Inside);
}