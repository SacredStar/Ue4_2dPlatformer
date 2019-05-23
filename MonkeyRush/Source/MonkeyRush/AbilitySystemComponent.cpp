// CopyRight Shmelevka


#include "AbilitySystemComponent.h"

// Sets default values for this component's properties
UAbilitySystemComponent::UAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//Setup Stats
	Intellect = 5;
	Winsdom = 5;
	Strengh = 5;
	Agility = 5;
	Health = Strengh;
	Mana = (Intellect * Winsdom);
}


// Called when the game starts
void UAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAbilitySystemComponent::CastSpell()
{
	FVector SpellCastOffset = GetOwner()->GetActorLocation() + FVector(10.f,0.f,0.f);
	FRotator SpellCastRotator = GetOwner()->GetActorRotation(); 
	
	//Spawn Parameters
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.Instigator = GetOwner()->Instigator;
	
	//Creating a FireBall
	AFireBall* FireBall = GetWorld()->SpawnActor<AFireBall>(FireBallClass,SpellCastOffset,SpellCastRotator,SpawnParameters);
	UE_LOG(LogTemp, Warning, TEXT("Cast Spelling Function Reporting!"));
}

void UAbilitySystemComponent::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack Function Reporting!"));
	//TODO
}

