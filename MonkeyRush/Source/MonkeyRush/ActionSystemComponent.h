// CopyRight Shmelevka

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONKEYRUSH_API UActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
		UActionSystemComponent();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Called Functions for Actions */
		UFUNCTION()
		void Slide();

		//Fuction for Start Attack if no Cast spell/Attack +  no Falling down, alse Disable Movement
		UFUNCTION()
		void Attack();
		
};
