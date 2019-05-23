// CopyRight Shmelevka

#include "ActionSystemComponent.h"

// Sets default values for this component's properties
UActionSystemComponent::UActionSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActionSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//FIxed: 
void UActionSystemComponent::Attack()
{
		//GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
		
		
		//UE_LOG(LogTemp, Warning, TEXT("Atacking Function Reporting!"));
	
}


//TODO
void UActionSystemComponent::Slide()
{
	//FVector Launch_Dir = FVector(4000.f,0.f,0.f);
	//FHitResult hit;
	//AMonkeyRushCharacter::SlideAlongSurface(FVector(200.f,0.f,0.f),1.f,FVector(200.f,0.f,0.f),hit,false);
	/*if(	GetCharacterMovement()-> IsFalling() == true)
	{
		GetCharacterMovement()->StopActiveMovement();
	}*/
	//GetCharacterMovement()->AddImpulse(FVector(4000.f,0.f,0.f),true);
}
