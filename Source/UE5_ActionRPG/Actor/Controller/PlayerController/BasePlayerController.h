#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "BasePlayerController.generated.h"

UCLASS()
class UE5_ACTIONRPG_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess();
protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLookMouse(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
	void OnMouseL(const FInputActionValue& InputActionValue);
	
private:
	class ABasePlayer* Player;
};
