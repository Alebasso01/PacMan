// Fill out your copyright notice in the Description page of Project Settings.

#include "PacmanPawn.h"
#include "TestGridGameMode.h"
#include "Fruit.h"

APacmanPawn::APacmanPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// vettore di direzione inizializzato con zero (il pawn non si muove allo start del gioco fino a che non
	// viene premuto uno dei tasti W-A-S-D )
	LastInputDirection = FVector(0, 0, 0);
	LastValidInputDirection = FVector(0, 0, 0);
	//posizione iniziale  del pawn nelle coordinate di griglia (6,13)
	CurrentGridCoords = FVector2D(8, 13);
}

void APacmanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//242 coins to eat to complete the game
void APacmanPawn::BeginPlay()
{
	Super::BeginPlay();
	//// posizione iniziale del pawn
	FVector2D StartNode = TheGridGen->GetXYPositionByRelativeLocation(GetActorLocation());
	LastNode = TheGridGen->TileMap[StartNode];
	coins = 0;
	total_coins = 242;
	life = 3;
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &APacmanPawn::TimerFunction, 3.0f, true, 0.5f);
	powermode = false;
	score = 0;
	coins2 = 0;
	coins3 = 0;
	CurrentMovementSpeed = 400.f;
}

void APacmanPawn::SetVerticalInput(float AxisValue)
{
	if (AxisValue == 0) return;
	const FVector Dir = (GetActorForwardVector() * AxisValue).GetSafeNormal();
	LastInputDirection = Dir.GetSafeNormal();
	SetNextNodeByDir(LastInputDirection);
}

void APacmanPawn::SetHorizontalInput(float AxisValue)
{
	if (AxisValue == 0) return;
	const FVector Dir = (GetActorRightVector() * AxisValue).GetSafeNormal();
	LastInputDirection = Dir;
	SetNextNodeByDir(LastInputDirection);
}

void APacmanPawn::OnClick()
{
	FHitResult Hit = FHitResult(ForceInit);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	if (AGridBaseNode* CurrTile = Cast<AGridBaseNode>(Hit.GetActor()))
	{
		FVector2D CurrCoords = CurrTile->GetGridPosition();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Position x=%f  Y=%f "), CurrCoords.X, CurrCoords.Y));
	}
}

void APacmanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Bind Actions here
	InputComponent->BindAxis(TEXT("MoveForward"), this, &APacmanPawn::SetVerticalInput);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &APacmanPawn::SetHorizontalInput);
	// bind the OnClick function to InputComponent for test purpose
	InputComponent->BindAction("Click", IE_Pressed, this, &APacmanPawn::OnClick);
}

void APacmanPawn::HandleMovement()
{
	Super::HandleMovement();
	// si muove autonomamente fino a che il next node è walkable
	if (!TargetNode && !NextNode)
	{
		if (TheGridGen->IsNodeValidForWalk(TheGridGen->GetNextNode(CurrentGridCoords, LastInputDirection)))
		{
			SetLastValidDirection(LastInputDirection);
		}
		SetNodeGeneric(LastValidInputDirection);
	}
}

void APacmanPawn::SetTargetNode(AGridBaseNode* Node)
{
	Super::SetTargetNode(Node);
}

void APacmanPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto PointNode = Cast<AGridBaseNode>(OtherActor);

	//if walk on a powernode increase the speed
	//count the number of coins token
	if (PointNode && PointNode->CanBeEat())
	{
		if (PointNode->IsPowered())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("power eaten")));
			CurrentMovementSpeed = 450.0f;
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &APacmanPawn::GetPowerOff, 6, true);
			powermode = true;
			PointNode->Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PointNode->StaticMesh->SetVisibility(false);
			PointNode->IsEatable = false;
			score = score + 10;
			GameMode->FrightnedMode();	
			if (life == 2)
			{
				coins2 = coins2 + 1;
			}
			else if (life == 1)
			{

				coins3 = coins3 + 1;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("coins = %d"), coins));
		}
		else if (PointNode->IsFruit())
		{
			PointNode->Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PointNode->StaticMesh->SetVisibility(false);
			PointNode->IsEatable = false;
			score = score + 100;
			if (life == 2)
			{
				coins2 = coins2 + 1;
			}
			else if (life == 1)
			{
				coins3 = coins3 + 1;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("coins = %d"), coins));
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("coin eaten %d"), coins));
			PointNode->Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PointNode->StaticMesh->SetVisibility(false);
			PointNode->IsEatable = false;
			score = score + 1;
			if (life == 2)
			{
				coins2 = coins2 + 1;
			}
			else if (life == 1)
			{
				coins3 = coins3 + 1;
			}
		}
		if (life == 3)
		{
			if (coins == 1)
			{
				GameMode->PinkyTeleport();
			}
			if (coins == 30)
			{
				GameMode->InkyTeleport();
			}
			if (coins == 90)
			{
				GameMode->ClydeTeleport();
			}
		}
		else if(life == 2)
		{
			if (coins2 == 7)
			{
				GameMode->PinkyTeleport();
			}
			if (coins2 == 17)
			{
				GameMode->InkyTeleport();
			}
			if (coins2 == 32)
			{
				GameMode->ClydeTeleport();
			}
		}
		else if (life == 1)
		{
			if (coins3 == 7)
			{
				GameMode->PinkyTeleport();
			}
			if (coins3 == 17)
			{
				GameMode->InkyTeleport();
			}
			if (coins3 == 32)
			{
				GameMode->ClydeTeleport();
			}
		}

		if (coins == 70 || coins == 170)
		{
			GameMode->SpawnFruit();
		}
		EatenCoin();
	}
	if (GetCoin() == total_coins) {
		GameMode->SetMessage(TEXT("YOU WIN"));
		Destroy();
	}
}

void APacmanPawn::EatenCoin()
{
	coins++;
}

int APacmanPawn::GetCoin()
{
	return coins;
}

void APacmanPawn::GetPowerOff()
{
	CurrentMovementSpeed = 400.0f;
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	powermode = false;
}

bool APacmanPawn::GetPowerMode()
{
	return powermode;
}

int32 APacmanPawn::GetScore()
{
	return score;
}
void APacmanPawn::RespawnPacman()
{	
	SetNextNode(*(TeleportNode.Find(FVector2D(8, 13))));
	SetTargetNode(NextNode);
	LastNode = *(TeleportNode.Find(FVector2D(8, 13)));
	const FVector Respawn(850.0f, 1350.0f, GetActorLocation().Z);
	SetActorLocation(Respawn);
	GameMode->ResetPosition();
}

void APacmanPawn::DeathManager()
{
	life = life - 1;
	if (life != 0)
	{
		RespawnPacman();
	}
	else
	{
		GameMode->SetMessage(TEXT("GAME OVER"));
		Destroy();
	}
}

int32 APacmanPawn::GetLife()
{
	return life;
}