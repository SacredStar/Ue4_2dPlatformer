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
	/** Creating a stats for my character  **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Intellect = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Winsdom = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Strengh = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Agility = 0;

	// Inherited Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Health = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Mana = 0;
	
};
