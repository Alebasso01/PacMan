// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGenerator.h"

constexpr int MapSizeX = 34;
constexpr int MapSizeY = 29;

// # - Wall
// B - Big Point
// N - Empty
// P - Player
//     Phantom:
//     - 1 - Blinky
//     - 2 - Pinky
//     - 3 - Inky
//     - 4 - Clyde
//    
// C - Cherry
// R - Ghost Respawn
// N - Ghost Area
// I - Invisible Not Walkable
// E - Ghost Exit

static char Map[MapSizeX][MapSizeY] = {
	"############################",
	"############################",
	"############################",
	"#                          #",
	"# ########## ## ########## #",
	"# #######    ##    ####### #",
	"#      ## ######## ##      #",
	"### ## ## ######## ## ## ###",
	"#B  ##                ##  B#",
	"# #### ##### ## ##### #### #",
	"# #### ##### ## ##### #### #",
	"#            ##            #",
	"###### ##V########V## ######",
	"###### ##V########V## ######",
	"###### ##VVVVVVFVVV## ######",
	"###### ##V########V## ######",
	"###### ##V#VIVIIV#V## ######",
	"TVVVVV VVV#VIVIIV#VVV VVVVVT",
	"###### ##V#VIVIIV#V## ######",
	"###### ##V###GG###V## ######",
	"###### ##VVVVVVVVVV## ######",
	"###### #####V##V##### ######",
	"###### ##### ## ##### ######",
	"#      ##    ##    ##      #",
	"# #### ## ######## ## #### #",
	"# #### ## ######## ## #### #",
	"#                          #",
	"# #### ##### ## ##### #### #",
	"#B#### ##### ## ##### ####B#",
	"# #### ##### ## ##### #### #",
	"#            ##            #",
	"############################",
	"############################",
	"############################",
};

AGridGenerator::AGridGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
	TileSize = 100.0f;
	SpawnOffset = FVector(TileSize);
}

void AGridGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateGrid();
}

void AGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TMap<FVector2D, AGridBaseNode*> AGridGenerator::GetTileMAp()
{
	return TileMap;
}

void AGridGenerator::GenerateGrid()
{
	for (int x = 0; x < MapSizeX; x++)
	{
		for (int y = 0; y < MapSizeY - 1; y++)
		{
			const char MapTile = Map[x][y];

			FVector OffsetVector(x * SpawnOffset.X, y * SpawnOffset.Y, 0);
			// imposto le coordinate spaziali per la funzione di spawn della tile
			const FVector CurrentSpawnPosition = GetActorLocation() + OffsetVector;
			// questa funzione spawna una nuova tile
			const auto SpawnedNode = SpawnNodeActorById(MapTile, CurrentSpawnPosition);
			// assegna le coordinate di griglia alla tile
			SpawnedNode->TileGridPosition = (FVector2D(x, y));
			// assegna le coordinate spaziali alla tile
			SpawnedNode->TileCoordinatesPosition = CurrentSpawnPosition;
			// aggiungo alle strutture dati il riferimento alla tile creata
			Grid.Add(SpawnedNode);
			TileMap.Add(FVector2D(x, y), SpawnedNode);
		}
	}
}

AGridBaseNode* AGridGenerator::GetNodeByCoords(const FVector2D Coords)
{
	if (Coords.X > MapSizeX - 1 || Coords.Y > MapSizeY - 2) return nullptr;
	if (Coords.X < 0 || Coords.Y < 0) return nullptr;
	return GetTileMAp()[FVector2D(Coords.X, Coords.Y)];
}

bool AGridGenerator::IsNodeReachableAndNextToCurrentPosition(const FVector2D CurrentCoordinates, const FVector2D TargetCoords)
{
	const float DistX = FMath::Abs(CurrentCoordinates.X - TargetCoords.X);
	const float DistY = FMath::Abs(CurrentCoordinates.Y - TargetCoords.Y);
	if (DistX > 1 || DistY > 1) return false;
	AGridBaseNode* const N = GetNodeByCoords(TargetCoords);
	if (N && N->EWalkableId == NotWalkable) return false;
	return true;
}

AGridBaseNode* AGridGenerator::GetClosestNodeFromMyCoordsToTargetCoords(const FVector2D StartCoords, const FVector2D TargetCoords, FVector IgnoredDir)
{
	const TArray<FDirNode> Neighbours = GetNodeNeighbours(GetNodeByCoords(StartCoords));
	float Dist = FLT_MAX;
	AGridBaseNode* ReturnNode = nullptr;
	for (FDirNode FDirNode : Neighbours)
	{
		if (FDirNode.Node == nullptr || FDirNode.Dir == IgnoredDir || FDirNode.Node->EWalkableId == NotWalkable)
			continue;
		
		const float TempDist = FVector2D::Distance(FDirNode.Node->GetGridPosition(), TargetCoords);
		if (TempDist < Dist)
		{
			Dist = TempDist;
			ReturnNode = FDirNode.Node;
		}
	}
	return ReturnNode;
}

TArray<FDirNode> AGridGenerator::GetNodeNeighbours(const AGridBaseNode* Node)
{
	TArray<FDirNode> Vec;
	if (Node)
	{	Vec.Add(FDirNode(GetNextNode(Node->GetGridPosition(), FVector::ForwardVector), FVector::ForwardVector));
		Vec.Add(FDirNode(GetNextNode(Node->GetGridPosition(), FVector::RightVector), FVector::RightVector));
		Vec.Add(FDirNode(GetNextNode(Node->GetGridPosition(), -FVector::ForwardVector), -FVector::ForwardVector));
		Vec.Add(FDirNode(GetNextNode(Node->GetGridPosition(), FVector::LeftVector), FVector::LeftVector));
	}
	return Vec;
}


AGridBaseNode* AGridGenerator::SpawnNodeActorById(char CharId, FVector Position) const
{
	AGridBaseNode* Node;
	TSubclassOf<AGridBaseNode> ClassToSpawn = AGridBaseNode::StaticClass();

	bool empty = false;

	if (CharId == '#')
	{
		ClassToSpawn = WallNode;
	}
	else if (CharId == 'B')
	{
		ClassToSpawn = PowerNode;
		
	}
	else if (CharId == 'N')
	{
		ClassToSpawn = NullNode;
			}
	else if (CharId == 'P')
	{
		ClassToSpawn = CharacterNode;
		empty = true;
	}
	else if (CharId == '1')
	{
		ClassToSpawn = BlinkyNode;
		empty = true;
			}
	else if (CharId == '2')
	{
		ClassToSpawn = PinkyNode;
		empty = true;
	}
		
	else if (CharId == '3')
	{
		ClassToSpawn = InkyNode;
		empty = true;
	}
	else if (CharId == '4')
	{
		ClassToSpawn = ClydeNode;
		empty = true;
	}
	else if (CharId == 'R')
	{
		ClassToSpawn = GhostRespawnNode;
		empty = true;
	}
	else if (CharId == 'T')
	{
		ClassToSpawn = TeleportNode;
		empty = true;
	}
	else if (CharId == 'N')
	{
		ClassToSpawn = GhostAreaNode;
	}
	else if (CharId == 'I')
	{
		ClassToSpawn = InvisibleWallNode;
	}
	else if (CharId == 'E')
	{
		ClassToSpawn = GhostExitNode;
		empty = true;
	}
	else if (CharId == 'V')
	{
		ClassToSpawn = LabyrinthNode;
		empty = true;
	}
	else if (CharId == 'F')
	{
		ClassToSpawn = Fruit;
		
		empty = true;
	}
	else if (CharId == 'G')
	{
		ClassToSpawn = Gate;

	}
	else
	{
		ClassToSpawn = LabyrinthNode;
	}
	Node = GetWorld()->SpawnActor<AGridBaseNode>(ClassToSpawn, Position, FRotator::ZeroRotator);
	//if empty spawn the tile without the eatable mesh
	if (empty == true)
	{
		Node->Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Node->StaticMesh->SetVisibility(false);
		Node->IsEatable = false;
		empty = false;

	}
	return Node;
}


bool AGridGenerator::IsNodeValidForWalk(AGridBaseNode* Node)
{
	if (Node == nullptr) return false;
	if (Node->EWalkableId == NotWalkable) return false;

	return true;
}

AGridBaseNode* AGridGenerator::GetNextNode(const FVector2D StartCoords, FVector InputDir)
{

	const float RequestedX = StartCoords.X + InputDir.X;
	const float RequestedY = StartCoords.Y + InputDir.Y;
	const float ClampedX = FMath::Clamp(RequestedX, 0.f, MapSizeX - 1);
	const float ClampedY = FMath::Clamp(RequestedY, 0.f, MapSizeY - 2);
	AGridBaseNode* PossibleNode = GetTileMAp()[FVector2D(ClampedX, ClampedY)];

	if (RequestedX > ClampedX || RequestedX < 0)
	{
		PossibleNode = nullptr;
	}
	if (RequestedY > ClampedY || RequestedY < 0)
	{
		PossibleNode = nullptr;
	}
	return PossibleNode;
}

FVector2D AGridGenerator::GetPosition(const FHitResult& Hit)
{
	return Cast<AGridBaseNode>(Hit.GetActor())->GetGridPosition();
}

TArray<AGridBaseNode*>& AGridGenerator::GetTileArray()
{
	return Grid;
}

FVector AGridGenerator::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY)
{
	return  TileSize * FVector(InX, InY, 0);
}

FVector2D AGridGenerator::GetXYPositionByRelativeLocation(const FVector& Location)
{
	double x = floor(Location[0] / (TileSize));
	double y = floor(Location[1] / (TileSize));
	return FVector2D(x, y);
}

FVector2D AGridGenerator::GetTwoDOfVector(FVector DDDVector)
{
	return FVector2D(DDDVector.X, DDDVector.Y);
}

FVector AGridGenerator::GetThreeDOfTwoDVector(FVector2D DDDVector)
{
	return FVector(DDDVector.X, DDDVector.Y, 0);
}

