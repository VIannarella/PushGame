// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Trying_to_puzzle_2EditorTarget : TargetRules
{
	public Trying_to_puzzle_2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Trying_to_puzzle_2" } );
	}
}
