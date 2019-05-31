// CopyRight Shmelevka

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellProjectile.h"
#include "TimerManager.h"
#include "AbilitySystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
	class MONKEYRUSH_API UAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilitySystemComponent();

	/** Creating a stats for my character  **/
	UPROPERTY(BlueprintReadWrite,Category = Stats)
	int32 Intellect=0;
	UPROPERTY(BlueprintReadWrite,Category = Stats)
	int32 Winsdom=0;
	UPROPERTY(BlueprintReadWrite,Category = Stats)
	int32 Strengh=0;
	UPROPERTY(BlueprintReadWrite,Category = Stats)
	int32 Agility=0;

	// Inherited Stats
	UPROPERTY(BlueprintReadWrite,Category = Stats)
	int32 Health = 0;
	UPROPERTY(BlueprintReadWrite,Category = Stats)
	int32 Mana=0;

protected:
	// Called when the game starts
	void BeginPlay() override;

	/*     / For  Spell's    */
	// Location From where start to Fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellCasting)
	FVector SpellCastOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellCasting)
	FTransform SpellCastTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellCasting)
	FRotator SpellCastRotator;

public:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void CastSpell();

	UFUNCTION()
	void Attack();

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASpellProjectile> SpellClass;
};
