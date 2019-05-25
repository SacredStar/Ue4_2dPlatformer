// Copyright Shmelevka & Mishutka

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MONKEYRUSH_API UMyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	FORCEINLINE void TrySlideAlongSurf(FVector& Delta, float Time, FVector& Normal, FHitResult& HitsResults,bool bHandle) { SlideAlongSurface( Delta,Time,Normal,HitsResults,bHandle); }
};
