// Copyright Shmelevka & Mishutka


#include "NPC_Neutral.h"

// Sets default values
ANPC_Neutral::ANPC_Neutral()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC_Neutral::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC_Neutral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC_Neutral::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

