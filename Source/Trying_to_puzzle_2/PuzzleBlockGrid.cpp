// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleBlockGrid.h"
#include "PuzzleBlock.h"
#include "PuzzlePiece.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

// Sets default values
APuzzleBlockGrid::APuzzleBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 4;
	BlockSpacing = 300.f;

}

// Called when the game starts or when spawned
void APuzzleBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

																// Make postion vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		APuzzleBlock* NewBlock = GetWorld()->SpawnActor<APuzzleBlock>(BlockLocation, FRotator(0, 0, 0));

		
		PuzzleBlockArray.Add(NewBlock);

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
			NewBlock->SetBlockIndex(BlockIndex);
			if (BlockIndex == 0 || BlockIndex == 7)
			{
				APuzzlePiece* NewPiece = GetWorld()->SpawnActor<APuzzlePiece>(BlockLocation, FRotator(0, 0, 0));
				if (NewPiece != nullptr)
				{
					NewPiece->OwningGrid = this;
					NewPiece->SetCurrentBlock(NewBlock);
					NewPiece->SetCurrentBlockIndex(BlockIndex);
				}
			}
		}
	}
	
}



void APuzzleBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

void APuzzleBlockGrid::MovePiece(APuzzleBlock* MoveToBlock)
{
	///Unhighlight Available moves
	HighlightAvailableMoves(ActivePiece->GetCurrentBlockIndex(), false);

	///Update Active Piece Location
	ActivePiece->ChangeLocation(MoveToBlock->GetActorLocation());

	///Set new currentblock and index for active piece
	ActivePiece->SetCurrentBlock(MoveToBlock);
	ActivePiece->SetCurrentBlockIndex(MoveToBlock->GetBlockIndex());

	///Change piece material back to base material
	ActivePiece->Highlight(false);

	///Deselect active piece
	ActivePiece = nullptr;

	return;
}

bool APuzzleBlockGrid::CheckMove(AActor* Move)
{
	//check if move is valid

	//return true if so

	return false;
}

void APuzzleBlockGrid::SetActivePiece(APuzzlePiece* SelectedPiece)
{
	ActivePiece = SelectedPiece;
	return;
}

void APuzzleBlockGrid::HighlightAvailableMoves(int32 CurrentBlockIndex, bool MakeActive)
{

	//Highlight surrounding blocks 
	if (CurrentBlockIndex >= (Size))
	{
		PuzzleBlockArray[CurrentBlockIndex - Size]->Highlight(MakeActive);
	}
	if (CurrentBlockIndex % Size != 0)
	{
		PuzzleBlockArray[CurrentBlockIndex - 1]->Highlight(MakeActive);
	}
	if (CurrentBlockIndex % Size != Size - 1)
	{
		PuzzleBlockArray[CurrentBlockIndex + 1]->Highlight(MakeActive);
	}
	if ((CurrentBlockIndex + Size) < (Size*Size))
	{
		PuzzleBlockArray[CurrentBlockIndex + Size]->Highlight(MakeActive);
	}
	return;
}

#undef LOCTEXT_NAMESPACE

