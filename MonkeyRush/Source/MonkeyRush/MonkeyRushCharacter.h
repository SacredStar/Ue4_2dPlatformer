// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GameFramework/Character.h"
#include "MyCharacterMovementComponent.h"
#include "MonkeyRushCharacter.generated.h"


class UTextRenderComponent;

/**
 * This class is the default character for MonkeyRush, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
UCLASS(config=Game)
class AMonkeyRushCharacter : public APaperCharacter
{
	GENERATED_BODY()

protected:
	/*             //Animations //  */
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;
	
	//The Animation to play while Attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* AttackAnimation;

	//The animation to play while SpellCast
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* SpellCastAnimation;

	//The Animation to play while Jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	// The animation to play while StartSliding 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* SlideAnimation;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	void UpdateCharacter();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

private:
	//Custom Character Movement
	UMyCharacterMovementComponent* MovementComponent;
	
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	
	/* Handle to manage the timer */
	FTimerHandle AttackTimerHandle;

	//Handle To manage StartCastingSpell
	FTimerHandle CastSpellTimerHandle;

	/* Handle to manage the timer */
	FTimerHandle DashTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dash, meta = (AllowPrivateAccess = "true"))
	float DashDisctance = 250.f;

	/** Called for side to side input */
	void MoveRight(float Value);

public:
	AMonkeyRushCharacter();
	AMonkeyRushCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable,Category="Movement")
	FORCEINLINE class UMyCharacterMovementComponent* GetMyMovementComponent() const { return  MovementComponent; }

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystemComponent;

	//Boolean Stats for StartAttacking
	UPROPERTY(VisibleAnywhere,Category = BooleanStats)
		bool bAttacking = false;
	//Boolean Stats For SpellCast
	UPROPERTY(VisibleAnywhere,Category = BooleanStats)
		bool bSpellCasting = false;
	//Boolean Stats For StartSliding
	UPROPERTY(VisibleAnywhere,Category = BooleanStats)
		bool bSliding = false;
	//Boolean Stats For movement
	UPROPERTY(VisibleAnywhere,Category = BooleanStats)
		bool bMovementRight;

	virtual void Tick(float DeltaSeconds) override;

	virtual void PostInitializeComponents() override;
	
	void StartAttacking();
	void StartCastingSpell();
	void StartSliding();

};
