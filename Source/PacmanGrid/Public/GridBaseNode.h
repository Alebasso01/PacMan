
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GridBaseNode.generated.h"

UENUM()
enum EWalkableId { NotWalkable, Walkable, Fruit };

UCLASS()
class PACMANGRID_API AGridBaseNode : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridBaseNode();

protected:
	virtual void BeginPlay() override;
	bool powered;
	bool fruit_node;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EWalkableId> EWalkableId = Walkable;
	void SetGridPosition(const double InX, const double InY);
	FVector2D GetGridPosition() const;
	UPROPERTY(EditAnywhere)
		FVector2D TileGridPosition;
	UPROPERTY(EditAnywhere)
		FVector TileCoordinatesPosition;
	FVector GetTileCoordinates();
	UPROPERTY(EditAnywhere)
		bool IsEatable;
	UFUNCTION(BlueprintCallable)
		bool CanBeEat();
	UFUNCTION(BlueprintCallable)
		bool IsPowered();
	UFUNCTION(BlueprintCallable)
		bool IsFruit();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* Collider;

};
