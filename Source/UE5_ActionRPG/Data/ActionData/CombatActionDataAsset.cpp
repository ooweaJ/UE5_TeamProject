#include "Data/ActionData/CombatActionDataAsset.h"

void UCombatActionDataAsset::SetData(AItem* InItem)
{
	InItem->SetItemInfoData(&ItemInfoData);
}
