#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"
#include "AIBaseCharacter.generated.h"

UCLASS()
class UE5_ACTIONRPG_API AAIBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAIBaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
