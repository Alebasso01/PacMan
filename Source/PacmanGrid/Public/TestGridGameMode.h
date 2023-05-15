// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridGenerator.h"
#include "GridPawn.h"
#include "PacmanPawn.h"
#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Pinky.h"
#include "GameFramework/GameMode.h"
#include "Fruit.h"
#include "TestGridGameMode.generated.h"

USTRUCT(BlueprintType)
struct FGridPawn_ptr_Struct {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		APacmanPawn* PacMan_ptr;

	UPROPERTY(VisibleAnywhere)
		ABlinky* Blinky_ptr;
	UPROPERTY(VisibleAnywhere)
		APinky* Pinky_ptr;
	UPROPERTY(VisibleAnywhere)
		AClyde* Clyde_ptr;
	UPROPERTY(VisibleAnywhere)
		AInky* Inky_ptr;
	UPROPERTY(VisibleAnywhere)
		AFruit* Fruit_ptr;
};

UCLASS()
class PACMANGRID_API ATestGridGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// TSubclassOf is a template class that provides UClass type safety.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGridGenerator> GridGeneratorClass;

	// reference to a GameField object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGridGenerator* GField;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<APacmanPawn> PacmanClass;

	UPROPERTY(EditDefaultsOnly)
	    TSubclassOf<ABlinky> BlinkyClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AInky> InkyClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AClyde> ClydeClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<APinky> PinkyClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFruit> FruitClass;

	UPROPERTY(VisibleAnywhere)
		APacmanPawn* PacmanPawn;

	UPROPERTY(VisibleAnywhere)
	    ABlinky* BlinkyPawn;

	UPROPERTY(VisibleAnywhere)
		AInky* InkyPawn;

	UPROPERTY(VisibleAnywhere)
	    AClyde* ClydePawn;

	UPROPERTY(VisibleAnywhere)
		APinky* PinkyPawn;

	UPROPERTY(VisibleAnywhere)
		AFruit* FruitPawn;

	ATestGridGameMode();

	virtual void BeginPlay() override;

	void FrightnedMode();
	void SpawnFruit();
	void PinkyTeleport();
	void ClydeTeleport();
	void InkyTeleport();
	void ResetPosition();

	UPROPERTY(EditAnywhere)
		FString CurrentMessage;
	UFUNCTION(BlueprintCallable)
		FString GetMessage();
	UFUNCTION(BlueprintCallable)
		void SetMessage(FString Message);

protected:
	FGridPawn_ptr_Struct GridPawn_references;
	
	
	
};
