// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MonkeyRushGameMode.h"
#include "MonkeyRushCharacter.h"

AMonkeyRushGameMode::AMonkeyRushGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AMonkeyRushCharacter::StaticClass();	
}
