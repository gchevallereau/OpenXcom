#include "../Ruleset/RuleItem.h"
#include "NoAmmoItem.h"

namespace OpenXcom
{
NoAmmoItem::NoAmmoItem(RuleItem * weapon) : BattleItem(NULL, NULL)
{
	_rules = new RuleItem("DUMMY");
	_rules->setDamageType(weapon->getDamageType());
	_rules->setBattleType(weapon->getBattleType());
	_rules->setHitAnimation(weapon->getHitAnimation());
	_rules->setHitSound(weapon->getHitSound());
	_rules->setBulletSprite(weapon->getBulletSprite());
	_rules->setBigSprite(weapon->getBigSprite());
	_rules->setPower(weapon->getPower());
}

int NoAmmoItem::getAmmoQuantity() const
{
	return 1;
}

NoAmmoItem::~NoAmmoItem()
{
	delete(_rules);
}
}
