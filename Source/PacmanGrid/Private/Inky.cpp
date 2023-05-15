// Fill out your copyright notice in the Description page of Project Settings.


#include "Inky.h"

AGridBaseNode* AInky::GetPlayerRelativeTarget()
{
	return APhantomPawn::GetPlayerRelativeTarget();
}

AInky::AInky()
{
	EGhostId = Inky;
	Blinky = Cast<ABlinky>(UGameplayStatics::GetActorOfClass(GetWorld(), ABlinky::StaticClass()));
}
void AInky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->GetTargetNode() == nullptr)
	{
		SetGhostTarget();
	}
}

void AInky::SetGhostTarget()
{
	const AGridBaseNode* Target = GetPlayerRelativeTarget();
	if (chase == true && frightned == false && scatter == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 11))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(16, 11)));

		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 11))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 11)));
		}
		else
		{
			if (GetPlayer()->GetLastValidDirection() == FVector(0, 1, 0))
			{
				FVector2D Inky_Target = FVector2D(GetPlayer()->GetLastNodeCoords().X + 2, GetPlayer()->GetLastNodeCoords().Y);
				FVector2D Blinky_Position = Blinky->GetLastNodeCoords();

				FVector2D Difference;
				Difference.X = abs(Inky_Target.X - Blinky_Position.X);
				Difference.Y = abs(Inky_Target.Y - Blinky_Position.Y);

				if (Inky_Target.X >= Blinky_Position.X) {
					Inky_Target.X = Inky_Target.X + Difference.X;
				}
				if (Inky_Target.X < Blinky_Position.X)
				{
					Inky_Target.X = Inky_Target.X - Difference.X;
				}

				if (Inky_Target.Y >= Blinky_Position.Y) {
					Inky_Target.Y = Inky_Target.Y + Difference.Y;
				}
				if (Inky_Target.Y < Blinky_Position.Y)
				{
					Inky_Target.Y = Inky_Target.Y - Difference.Y;
				}
				if (Inky_Target.X > 32) {
					Inky_Target.X = 32;
				}
				if (Inky_Target.Y > 27) {
					Inky_Target.Y = 27;
				}
				if (Inky_Target.X < 0) {
					Inky_Target.X = 0;
				}
				if (Inky_Target.Y < 0) {
					Inky_Target.Y = 0;
				}
				Target = *(TeleportNode.Find(Inky_Target));
			}
			else if (GetPlayer()->GetLastValidDirection() == FVector(0, -1, 0))
			{
				FVector2D Inky_Target = FVector2D(GetPlayer()->GetLastNodeCoords().X + 2, GetPlayer()->GetLastNodeCoords().Y);
				FVector2D Blinky_Position = Blinky->GetLastNodeCoords();

				FVector2D Difference;
				Difference.X = abs(Inky_Target.X - Blinky_Position.X);
				Difference.Y = abs(Inky_Target.Y - Blinky_Position.Y);

				if (Inky_Target.X >= Blinky_Position.X) {
					Inky_Target.X = Inky_Target.X + Difference.X;
				}
				if (Inky_Target.X < Blinky_Position.X)
				{
					Inky_Target.X = Inky_Target.X - Difference.X;
				}

				if (Inky_Target.Y >= Blinky_Position.Y) {
					Inky_Target.Y = Inky_Target.Y + Difference.Y;
				}
				if (Inky_Target.Y < Blinky_Position.Y)
				{
					Inky_Target.Y = Inky_Target.Y - Difference.Y;
				}
				if (Inky_Target.X > 32) {
					Inky_Target.X = 32;
				}
				if (Inky_Target.Y > 27) {
					Inky_Target.Y = 27;
				}
				if (Inky_Target.X < 0) {
					Inky_Target.X = 0;
				}
				if (Inky_Target.Y < 0) {
					Inky_Target.Y = 0;
				}
				Target = *(TeleportNode.Find(Inky_Target));
			}
			else if (GetPlayer()->GetLastValidDirection() == FVector(1, 0, 0))
			{
				FVector2D Inky_Target = FVector2D(GetPlayer()->GetLastNodeCoords().X + 2, GetPlayer()->GetLastNodeCoords().Y);
				FVector2D Blinky_Position = Blinky->GetLastNodeCoords();

				FVector2D Difference;
				Difference.X = abs(Inky_Target.X - Blinky_Position.X);
				Difference.Y = abs(Inky_Target.Y - Blinky_Position.Y);

				if (Inky_Target.X >= Blinky_Position.X) {
					Inky_Target.X = Inky_Target.X + Difference.X;
				}
				if (Inky_Target.X < Blinky_Position.X)
				{
					Inky_Target.X = Inky_Target.X - Difference.X;
				}

				if (Inky_Target.Y >= Blinky_Position.Y) {
					Inky_Target.Y = Inky_Target.Y + Difference.Y;
				}
				if (Inky_Target.Y < Blinky_Position.Y)
				{
					Inky_Target.Y = Inky_Target.Y - Difference.Y;
				}
				if (Inky_Target.X > 32) {
					Inky_Target.X = 32;
				}
				if (Inky_Target.Y > 27) {
					Inky_Target.Y = 27;
				}
				if (Inky_Target.X < 0) {
					Inky_Target.X = 0;
				}
				if (Inky_Target.Y < 0) {
					Inky_Target.Y = 0;
				}
				Target = *(TeleportNode.Find(Inky_Target));
			}
			else if (GetPlayer()->GetLastValidDirection() == FVector(-1, 0, 0))
			{
				FVector2D Inky_Target = FVector2D(GetPlayer()->GetLastNodeCoords().X + 2, GetPlayer()->GetLastNodeCoords().Y);
				FVector2D Blinky_Position = Blinky->GetLastNodeCoords();

				FVector2D Difference;
				Difference.X = abs(Inky_Target.X - Blinky_Position.X);
				Difference.Y = abs(Inky_Target.Y - Blinky_Position.Y);

				if (Inky_Target.X >= Blinky_Position.X) {
					Inky_Target.X = Inky_Target.X + Difference.X;
				}
				if (Inky_Target.X < Blinky_Position.X)
				{
					Inky_Target.X = Inky_Target.X - Difference.X;
				}

				if (Inky_Target.Y >= Blinky_Position.Y) {
					Inky_Target.Y = Inky_Target.Y + Difference.Y;
				}
				if (Inky_Target.Y < Blinky_Position.Y)
				{
					Inky_Target.Y = Inky_Target.Y - Difference.Y;
				}
				if (Inky_Target.X > 32) {
					Inky_Target.X = 32;
				}
				if (Inky_Target.Y > 27) {
					Inky_Target.Y = 27;
				}
				if (Inky_Target.X < 0) {
					Inky_Target.X = 0;
				}
				if (Inky_Target.Y < 0) {
					Inky_Target.Y = 0;
				}
				Target = *(TeleportNode.Find(Inky_Target));
			}
		}
	}
	else if (scatter == true && chase == false && frightned == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 11))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(16, 11)));

		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 11))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 11)));
		}
		else
		{
			Target = *(TeleportNode.Find(FVector2D(4, 16)));
		}
	}
	else if (frightned == true && chase == false && scatter == false && eaten == false)
	{
		if (LastNode->GetGridPosition() == FVector2D(18, 11))
		{
			FVector update_direction = FVector(-1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(16, 11)));

		}
		else if (LastNode->GetGridPosition() == FVector2D(16, 11))
		{
			FVector update_direction = FVector(1, 0, 0);
			SetLastValidDirection(update_direction);
			Target = *(TeleportNode.Find(FVector2D(18, 11)));
		}
		else
		{
			FVector2D newTarget = APhantomPawn::RandomMovement();
			Target = *(TeleportNode.Find(newTarget));
		}
	}
	else if (eaten == true && frightned == false && chase == false && scatter == false)
	{
		CurrentMovementSpeed = 1000.0f;
		Target = *(TeleportNode.Find(FVector2D(20, 13)));
		if (LastNode->GetGridPosition() == FVector2D(20, 13))
		{
			TeleportInky();
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
void AInky::TeleportInky()
{
	SetNextNode(*(TeleportNode.Find(FVector2D(18, 11))));
	SetTargetNode(NextNode);
	LastNode = *(TeleportNode.Find(FVector2D(18, 11)));
	const FVector Inside(1850.0f, 1150.0f, GetActorLocation().Z);
	SetActorLocation(Inside);
}