// Copyright Shmelevka & Mishutka

#pragma once

#include "CoreMinimal.h"
#include "MonkeyRushCharacter.h"
#include "BaseEnemy.generated.h"

/**
 * Base Class Enemy derivered from AMonkeyRushCharacter which derived from Paper2dCharacter
 * 
 */
UCLASS()
class MONKEYRUSH_API ABaseEnemy : public AMonkeyRushCharacter
{
	GENERATED_BODY()
public:
	ABaseEnemy();
	
};
