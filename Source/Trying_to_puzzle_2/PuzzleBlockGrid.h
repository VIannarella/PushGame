// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBlockGrid.generated.h"

UCLASS()
class TRYING_TO_PUZZLE_2_API APuzzleBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;
	
public:	
	// Sets default values for this actor's properties
	APuzzleBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float BlockSpacing;

	UPROPERTY()
	class APuzzleBlock* ACurrentBlock;

	UPROPERTY()
	class APuzzlePiece* ACurrentPiece;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/** Handle the block being clicked */
	void AddScore();
	void MovePiece(APuzzleBlock* MoveToBlock);

	void SetActivePiece(APuzzlePiece*);
	void HighlightAvailableMoves(int32 CurrentBlockIndex, bool MakeActive);
	bool CheckMove(AActor* SelectedMove);

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }

private:
	TArray<APuzzleBlock*> PuzzleBlockArray;
	APuzzlePiece* ActivePiece;
	
};
