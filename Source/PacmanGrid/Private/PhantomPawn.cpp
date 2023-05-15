// Fill out your copyright notice in the Description page of Project Settings.


#include "PhantomPawn.h"
#include "PacmanPawn.h"
#include "GridPawn.h"
#include "TestGridGameMode.h"
#include "Kismet/GameplayStatics.h"


APhantomPawn::APhantomPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlueMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlueMesh"));
	BlueMesh->SetupAttachment(Collider);
	BlueMesh->SetVisibility(false);
	WhiteMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WhiteMesh"));
	WhiteMesh->SetupAttachment(Collider);
	WhiteMesh->SetVisibility(false);
	EatenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EatenMesh"));
	EatenMesh->SetupAttachment(Collider);
	EatenMesh->SetVisibility(false);
	CurrentMovementSpeed = 370.f;

	flashes = 0;
}

void APhantomPawn::BeginPlay()
{
	Super::BeginPlay();
	FVector2D StartNode = TheGridGen->GetXYPositionByRelativeLocation(GetActorLocation());
	LastNode = TheGridGen->TileMap[StartNode];
	Player = Cast<APacmanPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APacmanPawn::StaticClass()));
	scatter = true;
	frightned = false;
	chase = false;
	eaten = false;
	save_scatter = scatter;
	save_chase = chase;
	counter = 1;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::SetChaseOn, 7, true);
}

void APhantomPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	const auto PN = Cast<APacmanPawn>(OtherActor);
	if (PN && frightned == true && PN->GetPowerMode() == true)
	{
		this->SetEatenOn();
	}
	else if (PN && frightned == false && PN->GetPowerMode() == false)
	{
		PN->DeathManager();
	}
	else if (eaten == true)
	{

	}
}

void APhantomPawn::OnNodeReached()
{
	Super::OnNodeReached();
}

APacmanPawn* APhantomPawn::GetPlayer() const
{
	return Player;
}

void APhantomPawn::SetSpeed(float Speed)
{
	CurrentMovementSpeed = Speed;
}

AGridBaseNode* APhantomPawn::GetPlayerRelativeTarget()
{
	return Player->GetLastNode();
}

void APhantomPawn::SetFrightnedOn()
{
	SetSpeed(250);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Frightned mode ON")));
	frightned = true;
	eaten = false;
	scatter = false;
	chase = false;
	SetTimerBluMesh();
	InvertDirection();
	contatore = 0;
}

void APhantomPawn::SetFrightnedOff()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Frightned mode OFF")));
	SetSpeed(370);
	if (save_scatter == true)
	{
		SetScatterOn();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, FString::Printf(TEXT("ero in scatter, torno in scatter")));
	}
	else
	{
		SetChaseOn();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("ero in chase, torno in case")));
	}
}
 
void APhantomPawn::SetScatterOn()
{
	counter += 1;
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	chase = false;
	scatter = true;
	frightned = false;
	eaten = false;
	save_scatter = scatter;
	save_chase = chase;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("scatter on")));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("COUNTER = %d"), counter));
	InvertDirection();
	if (counter < 5)
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::SetChaseOn, 7, true);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::SetChaseOn, 5, true);
	}
}

void APhantomPawn::SetChaseOn()
{
	counter += 1;
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	chase = true;
	scatter = false;
	frightned = false;
	eaten = false;
	save_scatter = scatter;
	save_chase = chase;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("chase on")));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("COUNTER = %d"), counter));
	InvertDirection();
	if (counter < 7)
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::SetScatterOn, 20, true);
	}
}

void APhantomPawn::SetTimerBluMesh()
{
	flashes = flashes + 1;
	WhiteMesh->SetVisibility(false);
	BlueMesh->SetVisibility(true);
	if (flashes < 2)
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::SetTimerWhiteMesh, 4, true);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::SetTimerWhiteMesh, 0.1, true);
	}
}

void APhantomPawn::SetTimerWhiteMesh()
{
	BlueMesh->SetVisibility(false);
	WhiteMesh->SetVisibility(true);
	flashes = flashes + 1;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("mesh numero %d"), counter));
	if (flashes > 20)
	{
		ResetMesh();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &APhantomPawn::SetTimerBluMesh, 0.1, true);
	}
}
void APhantomPawn::SetEatenMesh()
{
	EatenMesh->SetVisibility(true);
	BlueMesh->SetVisibility(false);
	WhiteMesh->SetVisibility(false);
}
void APhantomPawn::ResetMesh()
{
	EatenMesh->SetVisibility(false);
	BlueMesh->SetVisibility(false);
	WhiteMesh->SetVisibility(false);
	flashes = 0;
	InvertDirection();
	SetFrightnedOff();
}

void APhantomPawn::SetEatenOn()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	SetEatenMesh();
	eaten = true;
	frightned = false;
	scatter = false;
	chase = false;
}

void APhantomPawn::TeleportOutside()
{
	if (frightned == true)
	{
		SetNextNode(*(TeleportNode.Find(FVector2D(20, 13))));
		SetTargetNode(NextNode);
		LastNode = *(TeleportNode.Find(FVector2D(20, 13)));
		const FVector Outside(2050.0f, 1350.0f, GetActorLocation().Z);
		SetActorLocation(Outside);
	}
	else 
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		SetNextNode(*(TeleportNode.Find(FVector2D(20, 13))));
		SetTargetNode(NextNode);
		LastNode = *(TeleportNode.Find(FVector2D(20, 13)));
		const FVector Outside(2050.0f, 1350.0f, GetActorLocation().Z);
		SetActorLocation(Outside);
		SetFrightnedOff();
	}

}

void APhantomPawn::InvertDirection()
{
	if (GetLastValidDirection() == FVector(1, 0, 0))
	{
		FVector update_direction = FVector(-1, 0, 0);
		SetLastValidDirection(update_direction);
	}
	else if (GetLastValidDirection() == FVector(-1, 0, 0))
	{
		FVector update_direction = FVector(1, 0, 0);
		SetLastValidDirection(update_direction);
	}
	else if (GetLastValidDirection() == FVector(0, 1, 0))
	{
		FVector update_direction = FVector(0, -1, 0);
		SetLastValidDirection(update_direction);
	}
	else if (GetLastValidDirection() == FVector(0, -1, 0))
	{
		FVector update_direction = FVector(0, 1, 0);
		SetLastValidDirection(update_direction);
	}
}

FVector2D APhantomPawn::RandomMovement()
{
	int x = FMath::FRandRange(1, 10);
	int y = FMath::FRandRange(1, 10);
	FVector2D RandomTile = FVector2D(x, y);
	return RandomTile;
}

