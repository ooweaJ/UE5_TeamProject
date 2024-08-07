#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Weapon/BaseWeapon.h"
#include "GruxItem.generated.h"

UCLASS()
class UE5_ACTIONRPG_API AGruxItem : public ABaseWeapon
{
	GENERATED_BODY()
	
public:	
	AGruxItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	virtual void OnDefaultAction();
	virtual void OnDefaultAction2();
	virtual void OnDefaultAction3();
	virtual void OnSkillAction();
	virtual void OnSkillAction2();
	virtual void OnSkillAction3();
	virtual void OnUltimateAction();

	virtual void OffDefaultAction();
	virtual void OffDefaultAction2();
	virtual void OffDefaultAction3();
	virtual void OffSkillAction();
	virtual void OffSkillAction2();
	virtual void OffSkillAction3();
	virtual void OffUltimateAction();
	virtual void OnItemSkillAction();

	class AGrux* Grux;
};
