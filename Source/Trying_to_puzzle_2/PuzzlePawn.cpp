// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePawn.h"
#include "PuzzleBlock.h"
#include "PuzzlePiece.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values
APuzzlePawn::APuzzlePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APuzzlePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 8000.0f);
				TraceForBlock(Start, End, true);
			}
		}
		else
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, false);
		}
	}
}

void APuzzlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("OnResetVR", EInputEvent::IE_Pressed, this, &APuzzlePawn::OnResetVR);
	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &APuzzlePawn::TriggerClick);
}

void APuzzlePawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void APuzzlePawn::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void APuzzlePawn::TriggerClick()
{
	if (CurrentPieceFocus)
	{
		CurrentPieceFocus->HandleClicked();
		if (CurrentPieceSelected)
		{
			CurrentPieceSelected->CheckValidMove(CurrentPieceFocus);
			CurrentPieceSelected->Highlight(false);
		}
		CurrentPieceSelected = CurrentPieceFocus;
	}
}

void APuzzlePawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		APuzzlePiece* HitPiece = Cast<APuzzlePiece>(HitResult.Actor.Get());
		if (CurrentPieceFocus != HitPiece)
		{
			if (CurrentPieceFocus)
			{
				CurrentPieceFocus->Highlight(false);
			}
			if (HitPiece)
			{
				HitPiece->Highlight(true);
			}
			CurrentPieceFocus = HitPiece;
		}
	}
	else if (CurrentPieceFocus)
	{
		CurrentPieceFocus->Highlight(false);
		CurrentPieceFocus = nullptr;
	}
}

