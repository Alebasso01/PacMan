// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridPawn.h"
#include "PhantomPawn.generated.h"

/**
 * 
 */

UENUM()
enum EGhostId { Pinky, Blinky, Inky, Clyde };

UCLASS()
class PACMANGRID_API APhantomPawn : public AGridPawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	APhantomPawn();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnNodeReached() override;
	
	bool frightned;
	bool scatter;
	bool chase;
	bool save_scatter;
	bool save_chase;
	int contatore;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BlueMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* WhiteMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* EatenMesh;
	
private:
	UPROPERTY(VisibleAnywhere)
		class APacmanPawn* Player;
public:
	
	UFUNCTION()
		APacmanPawn* GetPlayer() const;
	UFUNCTION()
		void SetSpeed(float Speed);
	UFUNCTION()
		virtual AGridBaseNode* GetPlayerRelativeTarget();
	void SetFrightnedOn();
	void SetFrightnedOff();
	void SetScatterOn();
	void SetChaseOn();
	void SetTimerBluMesh();
	void SetTimerWhiteMesh();
	void SetEatenMesh();
	void ResetMesh();
	void SetEatenOn();
	void TeleportOutside();
	void InvertDirection();
	void FrightnedFinished();
	void ResetPosition();
	FTimerHandle Timer;	
	int counter;
	int flashes;
	bool eaten;
	FVector2D RandomMovement();

	

	

	
	
	
};
