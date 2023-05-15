// Fill out your copyright notice in the Description page of Project Settings.


#include "Pinky.h"

APinky::APinky()
{
	EGhostId = Pinky;
}

void APinky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->GetTargetNode() == nullptr)
	{
		SetGhostTarget();
	}
}

void APinky::SetGhostTarget()
{
	const AGridBaseNode* Target = GetPlayer()->GetLastNode();
	if (chase == true && frightned == false && scatter == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 13))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(16, 13)));

		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 13))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 13)));
		}
		else
		{
			if (GetPlayer()->GetLastValidDirection() == FVector(0, 1, 0))
			{

				FVector2D Pinky_Target = FVector2D(GetPlayer()->GetLastNodeCoords().X + 4, GetPlayer()->GetLastNodeCoords().Y);
				if (Pinky_Target.X > 32)
				{
					Pinky_Target.X = 32;
				}
				Target = *(TeleportNode.Find(Pinky_Target));		
			}
			else if (GetPlayer()->GetLastValidDirection() == FVector(0, -1, 0))
			{
				FVector2D Pinky_Target = FVector2D(GetPlayer()->GetLastNodeCoords().X - 4, GetPlayer()->GetLastNodeCoords().Y);

				if (Pinky_Target.X < 0)
				{
					Pinky_Target.X = 0;
				}
				Target = *(TeleportNode.Find(Pinky_Target));
			}
			else if (GetPlayer()->GetLastValidDirection() == FVector(1, 0, 0))
			{
				FVector2D Pinky_Target = FVector2D(GetPlayer()->GetLastNodeCoords().X + 4, GetPlayer()->GetLastNodeCoords().Y + 4);
				if (Pinky_Target.Y > 27 && Pinky_Target.X < 32)
				{
					Pinky_Target.Y = 27;
				}
				else if (Pinky_Target.X >= 33 && Pinky_Target.Y < 27)
				{
					Pinky_Target.X = 33;
				}
				else if (Pinky_Target.Y >= 27 && Pinky_Target.X >= 32)
				{
					Pinky_Target.Y = 27;
					Pinky_Target.X = 32;
				}
				Target = *(TeleportNode.Find(Pinky_Target));
			}
			else if (GetPlayer()->GetLastValidDirection() == FVector(-1, 0, 0))
			{

				FVector2D Pinky_Target = FVector2D(GetPlayer()->GetLastNodeCoords().X, GetPlayer()->GetLastNodeCoords().Y - 4);

				if (Pinky_Target.Y < 0)
				{
					Pinky_Target.Y = 0;
				}
				Target = *(TeleportNode.Find(Pinky_Target));
			}
		}

	}
	else if (scatter == true && chase == false && frightned == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 13))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(17, 13)));

		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 13))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(17, 13)));
		}
		else
		{
			Target = *(TeleportNode.Find(FVector2D(26, 3)));
		}
		
	}

	else if (frightned == true && chase == false && scatter == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 13))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(17, 13)));

		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 13))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(17, 13)));
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
			TeleportPinky();
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
void APinky::TeleportPinky()
{
	SetNextNode(*(TeleportNode.Find(FVector2D(18, 13))));
	SetTargetNode(NextNode);
	LastNode = *(TeleportNode.Find(FVector2D(18, 13)));
	const FVector Inside(1850.0f, 1350.0f, GetActorLocation().Z);
	SetActorLocation(Inside);
}

