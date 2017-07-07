// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePiece.generated.h"

UCLASS()
class TRYING_TO_PUZZLE_2_API APuzzlePiece : public AActor
{
	GENERATED_BODY()
	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;
	
public:	
	// Sets default values for this actor's properties
	APuzzlePiece();

	bool bIsActive;
	int32 CurrentBlockIndex;

	//Pointer to Base Puzzle Piece Material
	UPROPERTY()
	class UMaterial* BaseMaterial;

	//Pointer to Puzzle Piece material when selected
	UPROPERTY()
	class UMaterial* SelectedMaterial;

	//The grid the owns this puzzle piece
	UPROPERTY()
	class APuzzleBlockGrid* OwningGrid;

	//The Grid block that this puzzle piece is currently on
	UPROPERTY() 
	class APuzzleBlock* CurrentBlock;

	//Handle Block being clicked
	UFUNCTION()
	void PieceClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UFUNCTION()
	void OnFingerPressedPiece(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();

	void Highlight(bool bOn);

	void CheckValidMove(AActor*);

	void ChangeLocation(FVector);

	APuzzleBlock* GetCurrentBlock();
	void SetCurrentBlock(APuzzleBlock*);
	int32 GetCurrentBlockIndex();
	void SetCurrentBlockIndex(int32);

public:	
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }

	
	
};
