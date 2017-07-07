// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Trying_to_puzzle_2Target : TargetRules
{
	public Trying_to_puzzle_2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Trying_to_puzzle_2" } );
	}
}
