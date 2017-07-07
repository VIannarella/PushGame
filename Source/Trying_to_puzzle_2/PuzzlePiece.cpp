// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePiece.h"
#include "PuzzleBlock.h"
#include "PuzzleBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"


// Sets default values
APuzzlePiece::APuzzlePiece()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PieceMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> SelectedMaterial;
		FConstructorStatics()
			: PieceMesh(TEXT("/Game/StarterContent/Props/SM_Statue.SM_Statue"))
			, BaseMaterial(TEXT("/Game/StarterContent/Materials/M_Ground_Gravel.M_Ground_Gravel"))
			, SelectedMaterial(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"))
		{}
	};
	static FConstructorStatics ConstructorStatics;

	//DummyRoot scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy1"));
	RootComponent = DummyRoot;

	//Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh1"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PieceMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 55.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &APuzzlePiece::PieceClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &APuzzlePiece::OnFingerPressedPiece);

	//Save pointers to materials
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	SelectedMaterial = ConstructorStatics.SelectedMaterial.Get();

}

//Default funtion when piece clicked
void APuzzlePiece::PieceClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

//Default function on finger pressed
void APuzzlePiece::OnFingerPressedPiece(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

//Change Piece Location
void APuzzlePiece::ChangeLocation(FVector NewLocation)
{
	this->SetActorLocation(NewLocation, true, nullptr, ETeleportType::None);
}

//Function for when a piece is clicked
void APuzzlePiece::HandleClicked() {
	//if the piece is not already active, handle clicked
	if (!bIsActive)
	{
		bIsActive = true;

		//Change Material when selected
		BlockMesh->SetMaterial(0, SelectedMaterial);
		if (OwningGrid != nullptr)
		{
			// Get available moves
			OwningGrid->HighlightAvailableMoves(CurrentBlockIndex, true);
			OwningGrid->SetActivePiece(this);
			BlockMesh->SetMaterial(0, SelectedMaterial);
		}
	}
}

//Check Move Validity on block click
void APuzzlePiece::CheckValidMove(AActor* Selected)
{
	OwningGrid->CheckMove(Selected);
	return;
}

//Update the piece material 
void APuzzlePiece::Highlight(bool bOn)
{


	if (bOn)
	{
		BlockMesh->SetMaterial(0, SelectedMaterial);
	}
	else
	{
		bIsActive = false;
		BlockMesh->SetMaterial(0, BaseMaterial);
	}

}

APuzzleBlock* APuzzlePiece::GetCurrentBlock()
{
	return CurrentBlock;
}

void APuzzlePiece::SetCurrentBlock(APuzzleBlock* NewBlock)
{
	CurrentBlock = NewBlock;
}

int32 APuzzlePiece::GetCurrentBlockIndex()
{
	return CurrentBlockIndex;
}

void APuzzlePiece::SetCurrentBlockIndex(int32 NewBlockIndex)
{
	CurrentBlockIndex = NewBlockIndex;
}

