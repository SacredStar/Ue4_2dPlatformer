// CopyRight Shmelevka

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireBall.h"
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
	UPROPERTY(VisibleAnywhere,Category = Stats)
	int32 Intellect;
	UPROPERTY(VisibleAnywhere,Category = Stats)
	int32 Winsdom;
	UPROPERTY(VisibleAnywhere,Category = Stats)
	int32 Strengh;
	UPROPERTY(VisibleAnywhere,Category = Stats)
	int32 Agility;

	// Inherited Stats
	UPROPERTY(VisibleAnywhere,Category = Stats)
	int32 Health;
	UPROPERTY(VisibleAnywhere,Category = Stats)
	int32 Mana;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void CastSpell ();

	// Projectile class to spawn.
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class AFireBall> FireBallClass;
		
};
