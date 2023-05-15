// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGridGameMode.h"
#include "Containers/Array.h" 
#include "PacmanPawn.h"
#include "Kismet/GameplayStatics.h"


ATestGridGameMode::ATestGridGameMode()
{
	
}

void ATestGridGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	FVector GridPos(50.0f, 50.0f, 0.0f);
	if (GridGeneratorClass != nullptr)
	{
		GField = GetWorld()->SpawnActor<AGridGenerator>(GridGeneratorClass, GridPos, FRotationMatrix::MakeFromX(FVector(0, 0, 0)).Rotator());
	}; 

	GridPawn_references.Blinky_ptr = GetWorld()->SpawnActor<ABlinky>(BlinkyClass, FVector((100 * 20) + 50, (100 * 13) + 50, 5.0f), FRotator(0, 0, 0));
	GridPawn_references.Clyde_ptr = GetWorld()->SpawnActor<AClyde>(ClydeClass, FVector((100 * 18) + 50, (100 * 16) + 50, 5.0f), FRotator(0, 0, 0));
	GridPawn_references.Inky_ptr = GetWorld()->SpawnActor<AInky>(InkyClass, FVector((100 * 18) + 50, (100 * 11) + 50, 5.0f), FRotator(0, 0, 0));
	GridPawn_references.Pinky_ptr = GetWorld()->SpawnActor<APinky>(PinkyClass, FVector((100 * 18) + 50, (100 * 13) + 50, 5.0f), FRotator(0, 0, 0));

	AActor* CherryActor = UGameplayStatics::GetActorOfClass(GetWorld(),
		AFruit::StaticClass());
	GridPawn_references.Fruit_ptr = Cast<AFruit>(CherryActor);
}

void ATestGridGameMode::FrightnedMode()
{
	
	if (GridPawn_references.Blinky_ptr != nullptr)
	{
		GridPawn_references.Blinky_ptr->SetFrightnedOn();
	}
	if (GridPawn_references.Clyde_ptr != nullptr)
	{
		GridPawn_references.Clyde_ptr->SetFrightnedOn();
	}
	if (GridPawn_references.Inky_ptr != nullptr)
	{
		GridPawn_references.Inky_ptr->SetFrightnedOn();
	}
	if (GridPawn_references.Pinky_ptr != nullptr)
	{
		GridPawn_references.Pinky_ptr->SetFrightnedOn();
	}
}


void ATestGridGameMode::SpawnFruit()
{
	if (GridPawn_references.Fruit_ptr != nullptr)
	{
		GridPawn_references.Fruit_ptr->SetVisibilityOn();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("puntatore alla frutta nullo")));
	}
}

void ATestGridGameMode::PinkyTeleport()
{
	if (GridPawn_references.Pinky_ptr != nullptr)
	{
		GridPawn_references.Pinky_ptr->TeleportOutside();
	}
}

void ATestGridGameMode::InkyTeleport()
{
	if (GridPawn_references.Inky_ptr != nullptr)
	{
		GridPawn_references.Inky_ptr->TeleportOutside();
	}
}
void ATestGridGameMode::ClydeTeleport()
{
	if (GridPawn_references.Clyde_ptr != nullptr)
	{
		GridPawn_references.Clyde_ptr->TeleportOutside();
	}
}

void ATestGridGameMode::ResetPosition()
{
	GridPawn_references.Blinky_ptr->TeleportBlinky();
	GridPawn_references.Clyde_ptr->TeleportClyde();
	GridPawn_references.Inky_ptr->TeleportInky();
	GridPawn_references.Pinky_ptr->TeleportPinky();
}
void ATestGridGameMode::SetMessage(FString Message)
{
	CurrentMessage = Message;
}

FString ATestGridGameMode::GetMessage()
{
	return CurrentMessage;
}