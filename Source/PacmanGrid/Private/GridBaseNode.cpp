#include "GridBaseNode.h"

AGridBaseNode::AGridBaseNode()
{
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(Collider);
}

void AGridBaseNode::BeginPlay()
{
	Super::BeginPlay();
	powered = false;
	fruit_node = false;
}

void AGridBaseNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridBaseNode::SetGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY);
}

FVector2D AGridBaseNode::GetGridPosition() const
{
	return TileGridPosition;
}

FVector AGridBaseNode::GetTileCoordinates()
{
	return TileCoordinatesPosition;
}

bool AGridBaseNode::CanBeEat()
{
	return IsEatable;
}

bool AGridBaseNode::IsPowered()
{
	return powered;
}
bool AGridBaseNode::IsFruit()
{
	return fruit_node;
}


