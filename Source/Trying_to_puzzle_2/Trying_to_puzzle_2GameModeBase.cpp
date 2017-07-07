// Fill out your copyright notice in the Description page of Project Settings.

#include "Trying_to_puzzle_2GameModeBase.h"
#include "PuzzlePlayerController.h"
#include "PuzzlePawn.h"

ATrying_to_puzzle_2GameModeBase::ATrying_to_puzzle_2GameModeBase()
{
	//Define default pawn class
	DefaultPawnClass = APuzzlePawn::StaticClass();

	//Define default player controller
	PlayerControllerClass = APuzzlePlayerController::StaticClass();
}




