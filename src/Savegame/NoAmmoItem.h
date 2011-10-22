#ifndef OPENXCOM_NOAMMOITEM_H
#define OPENXCOM_NOAMMOITEM_H

#include "BattleItem.h"

namespace OpenXcom
{
class RuleItem;

class NoAmmoItem : public BattleItem
{
public:
	NoAmmoItem(RuleItem * weapon);
	~NoAmmoItem();
	int getAmmoQuantity() const;
};
}

#endif
