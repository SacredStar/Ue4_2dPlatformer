// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MonkeyRushCharacter.h"
#include "PaperFlipbookComponent.h"
//#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"


DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// AMonkeyRushCharacter

AMonkeyRushCharacter::AMonkeyRushCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);

	//arrow1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	//arrow1->SetupAttachment(RootComponent);


	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 3400.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->bAbsoluteRotation = true;
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
}


//////////////////////////////////////////////////////////////////////////
// Animation

void AMonkeyRushCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Animation to choose for 
	UPaperFlipbook* DesiredAnimation;

	//Animation Switching
	//TODO Add StartSliding Animation
	if (GetCharacterMovement()->IsFalling() == true)
	{
		DesiredAnimation = JumpAnimation;
		//UE_LOG(LogTemp, Display, TEXT("Jumping Animation Reporting!"));
	}
	else
	{
		if (bAttacking == false)
		{
			if (bSpellCasting == false)
			{
				if (PlayerSpeedSqr > 0.0f)
				{
					DesiredAnimation = RunningAnimation;
					//UE_LOG(LogTemp, Display, TEXT("Running Animation Reporting!"));
				}
				else
				{
					DesiredAnimation = IdleAnimation;
					//UE_LOG(LogTemp, Display, TEXT("Idle Animation Reporting!"));
				}
			}
			else
			{
				DesiredAnimation = SpellCastAnimation;
				//UE_LOG(LogTemp, Display, TEXT("SpellCast Animation Reporting!"));
			}
		}
		else
		{
			DesiredAnimation = AttackAnimation;
			//UE_LOG(LogTemp, Display, TEXT("StartAttacking Animation Reporting!"));
			//Attacking = false;
		}
	}

	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void AMonkeyRushCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();
}


//////////////////////////////////////////////////////////////////////////
// Input

void AMonkeyRushCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("AttackButton", IE_Pressed, this, &AMonkeyRushCharacter::StartAttacking);
	PlayerInputComponent->BindAction("SlideButton", IE_Pressed, this, &AMonkeyRushCharacter::StartSliding);
	PlayerInputComponent->BindAction("SpellCastButton", IE_Pressed, this, &AMonkeyRushCharacter::StartCastingSpell);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMonkeyRushCharacter::MoveRight);
}

void AMonkeyRushCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}


void AMonkeyRushCharacter::UpdateCharacter()
{
	UpdateAnimation();
	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			//UE_LOG(LogTemp, Display, TEXT("Left!"));
			bMovementRight = false;
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			//UE_LOG(LogTemp, Display, TEXT("Right!"));
			bMovementRight = true;
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

void AMonkeyRushCharacter::StartCastingSpell()
{
	FTimerDelegate TimerDelegate;
	//Lambda Function to  timer
	TimerDelegate.BindLambda([&]()
	{
		bSpellCasting = false;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		GetWorld()->GetTimerManager().ClearTimer(CastSpellTimerHandle);
	});

	if (bSpellCasting == false && bAttacking == false && 
		GetCharacterMovement()->IsFalling() == false && bSliding ==	false)
	{
		GetCharacterMovement()->DisableMovement();
		bSpellCasting = true;
		AbilitySystemComponent->CastSpell();
		//Timer to StopMovement and Animation changes,when fires set movement to normal and bSpellCast to false to continue Animation's
		GetWorld()->GetTimerManager().SetTimer(CastSpellTimerHandle, TimerDelegate, 0.6f, false);
	}
}

void AMonkeyRushCharacter::StartAttacking()
{
	FTimerDelegate TimerDelegate;
	//Lambda Function to timer
	TimerDelegate.BindLambda([&]()
	{
		bAttacking = false;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	});

	if (bSpellCasting == false && bAttacking == false && 
		GetCharacterMovement()->IsFalling() == false && bSliding ==	false)
	{
		GetCharacterMovement()->DisableMovement();
		//UE_LOG(LogTemp, Warning, TEXT("bAtacking Set True Reporting!"));
		bAttacking = true;
		AbilitySystemComponent->Attack();
		//Timer to Stop Movement and animation changes,when fires set movement to normal and bAttack to false to continue Animation's
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, TimerDelegate, 0.6f, false);
	}
}

void AMonkeyRushCharacter::StartSliding()
{
	UE_LOG(LogTemp, Warning, TEXT("StartSliding function Reporting!"));
	if (bSpellCasting == false && bAttacking == false &&
		GetCharacterMovement()->IsFalling() == false && bSliding == false)
	{
		bSliding = true;
		UE_LOG(LogTemp, Warning, TEXT("%s"), bAttacking)
		bSliding = false;
	}
}
