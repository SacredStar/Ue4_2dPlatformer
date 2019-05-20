// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
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

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Gameplay, meta=(AllowPrivateAccess="true"))
	//class UArrowComponent* arrow1;

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Creating a stats for my character **/
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
	
	//Boolean Stats for Atack,Casting
	UPROPERTY(VisibleAnywhere,Category = BooleanStats)
	bool Attacking = false;

	UPROPERTY(VisibleAnywhere,Category = BooleanStats)
	bool SpellCasting = false;

	UPROPERTY(VisibleAnywhere,Category = BooleanStats)
	bool isJumping = false;

	/* Handle to manage the timer */
	FTimerHandle AttackTimerHandle;

	FTimerHandle CastSpellTimerHandle;

	//Smth unknown
	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;

protected:

	/*              // For Fire Spell's and Attack's     */
	// Location From where start to Fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector SpellCastOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FTransform SpellCastTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FRotator SpellCastRotator;
	
	/*             //Animations //  */
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;
	
	//The Animation to play while Attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* AtackAnimation;

	//The animation to play while SpellCast
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* SpellCastAnimation;
	
	//The Animation to play while Jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* JumpAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/* 				//Movement Functions// 				/*
	/** Called for side to side input */
	void MoveRight(float Value);

	void UpdateCharacter();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	AMonkeyRushCharacter();

	//Fuction for Enable Movement + Set Attacking to False
	UFUNCTION()
	void setAttackingFalse ();

	//Function for Enable Movement+ Set SpellCast to False
	UFUNCTION()
	void setSpellCastingFalse ();
	
	/** Called Functions for Actions */

	//Fuction for Start Attack if no Cast spell/Attack +  no Falling down, alse Disable Movement
	UFUNCTION()
	void F_Attack();
	
	UFUNCTION()
	void F_CastSpell ();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Projectile class to spawn.
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class AFireBall> FireBallClass;
};
