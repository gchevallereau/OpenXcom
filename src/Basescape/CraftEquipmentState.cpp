/*
 * Copyright 2010 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "CraftEquipmentState.h"
#include <sstream>
#include "../Engine/Game.h"
#include "../Engine/Timer.h"
#include "../Resource/ResourcePack.h"
#include "../Engine/Language.h"
#include "../Engine/Font.h"
#include "../Engine/Palette.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Interface/TextList.h"
#include "../Ruleset/Ruleset.h"
#include "../Savegame/Base.h"
#include "../Savegame/Soldier.h"
#include "../Savegame/Craft.h"
#include "../Ruleset/RuleCraft.h"
#include "../Savegame/ItemContainer.h"
#include "../Ruleset/RuleItem.h"

namespace OpenXcom
{
/**
 * Helper to add items to craft equipment list
 * @param game The current Game
 * @param list The item's list
 * @param item The item to add
 * @param base The Base of the craft
 * @param craft The Craft to equip
 * @param row The current row
 * @param items The already added items
 * @return Wether or not item was added to the list
*/
inline bool addItems (Game * game, TextList * list, RuleItem * item, Base * base, Craft * craft, int & row, std::vector<std::string> & _items)
{
	if (base->getItems()->getItem(item->getType()) == 0 &&
	    craft->getItems()->getItem(item->getType()) == 0)
	{
		return false;
	}
	std::wstringstream ss, ss2;
	ss << base->getItems()->getItem(item->getType());
	ss2 << craft->getItems()->getItem(item->getType());

	std::wstring s = game->getLanguage()->getString(item->getType());
	if (item->getBattleType() == BT_AMMO)
	{
		s.insert(0, L"  ");
	}
	Uint8 color;
	if (craft->getItems()->getItem(item->getType ()) == 0)
	{
		color = Palette::blockOffset(13)+10;
	}
	else
	{
		color = Palette::blockOffset(13);
	}
	list->addRow(3, s.c_str(), ss.str().c_str(), ss2.str().c_str());
	list->setRowColor(row, color);
	_items.push_back(item->getType ());
	row++;
	return true;
}

/**
 * Initializes all the elements in the Craft Equipment screen.
 * @param game Pointer to the core game.
 * @param base Pointer to the base to get info from.
 * @param craft ID of the selected craft.
 */
CraftEquipmentState::CraftEquipmentState(Game *game, Base *base, unsigned int craft) : State(game), _sel(0), _base(base), _craft(craft)
{
	// Create objects
	_window = new Window(this, 320, 200, 0, 0);
	_btnOk = new TextButton(288, 16, 16, 176);
	_txtTitle = new Text(300, 16, 16, 7);
	_txtItem = new Text(144, 9, 16, 32);
	_txtStores = new Text(150, 9, 160, 32);
	_txtAvailable = new Text(110, 9, 16, 24);
	_txtUsed = new Text(110, 9, 130, 24);
	_lstEquipment = new TextList(288, 128, 8, 40);

	// Set palette
	_game->setPalette(_game->getResourcePack()->getPalette("BACKPALS.DAT")->getColors(Palette::blockOffset(2)), Palette::backPos, 16);

	add(_window);
	add(_btnOk);
	add(_txtTitle);
	add(_txtItem);
	add(_txtStores);
	add(_txtAvailable);
	add(_txtUsed);
	add(_lstEquipment);

	// Set up objects
	_window->setColor(Palette::blockOffset(15)+1);
	_window->setBackground(_game->getResourcePack()->getSurface("BACK04.SCR"));

	_btnOk->setColor(Palette::blockOffset(15)+1);
	_btnOk->setText(_game->getLanguage()->getString("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&CraftEquipmentState::btnOkClick);

	_txtTitle->setColor(Palette::blockOffset(15)+1);
	_txtTitle->setBig();
	Craft *c = _base->getCrafts()->at(_craft);
	std::wstring s;
	s = _game->getLanguage()->getString("STR_EQUIPMENT_FOR") + c->getName(_game->getLanguage());
	_txtTitle->setText(s);

	_txtItem->setColor(Palette::blockOffset(15)+1);
	_txtItem->setText(_game->getLanguage()->getString("STR_ITEM"));

	_txtStores->setColor(Palette::blockOffset(15)+1);
	_txtStores->setText(_game->getLanguage()->getString("STR_STORES"));

	_txtAvailable->setColor(Palette::blockOffset(15)+1);
	_txtAvailable->setSecondaryColor(Palette::blockOffset(13));
	std::wstringstream ss;
	ss << _game->getLanguage()->getString("STR_SPACE_AVAILABLE") << L'\x01'<< c->getRules()->getSoldiers() - c->getNumSoldiers();
	_txtAvailable->setText(ss.str());

	_txtUsed->setColor(Palette::blockOffset(15)+1);
	_txtUsed->setSecondaryColor(Palette::blockOffset(13));
	std::wstringstream ss2;
	ss2 << _game->getLanguage()->getString("STR_SPACE_USED") << L'\x01'<< c->getNumSoldiers();
	_txtUsed->setText(ss2.str());

	_lstEquipment->setColor(Palette::blockOffset(13)+10);
	_lstEquipment->setArrowColor(Palette::blockOffset(15)+1);
	_lstEquipment->setArrowColumn(203, ARROW_HORIZONTAL);
	_lstEquipment->setColumns(3, 154, 85, 41);
	_lstEquipment->setSelectable(true);
	_lstEquipment->setBackground(_window);
	_lstEquipment->setMargin(8);
	_lstEquipment->onLeftArrowPress((ActionHandler)&CraftEquipmentState::lstEquipmentLeftArrowPress);
	_lstEquipment->onLeftArrowRelease((ActionHandler)&CraftEquipmentState::lstEquipmentLeftArrowRelease);
	_lstEquipment->onRightArrowPress((ActionHandler)&CraftEquipmentState::lstEquipmentRightArrowPress);
	_lstEquipment->onRightArrowRelease((ActionHandler)&CraftEquipmentState::lstEquipmentRightArrowRelease);

	const std::map<std::string, RuleItem*> & ruleItems (_game->getRuleset()->getItems ());
	std::map<RuleItem*,std::vector<RuleItem*> > items;
	std::vector<RuleItem*> empty;
	std::map<std::string, int> *const baseItems (_base->getItems()->getContents());
	for(std::map<std::string, RuleItem*>::const_iterator i = ruleItems.begin (); i != ruleItems.end (); ++i)
	{
		if (!game->getSavedGame()->isItemAvailable (i->second, game->getRuleset()))
		{
			continue;
		}
		RuleItem * item = i->second;
		switch(item->getBattleType())
		{
		case BT_MELEE:
		case BT_GRENADE:
		case BT_PROXIMITYGRENADE:
		case BT_MEDIKIT:
		case BT_SCANNER:
		case BT_MINDPROBE:
		case BT_PSIAMP:
		case BT_FLARE:
		case BT_FIREARM:
		{
			items[item] = empty;
			if(item->getBattleType() != BT_FIREARM)
			{
				break;
			}
			std::vector<std::string> * ammos (item->getCompatibleAmmo());
			for(std::vector<std::string>::iterator j = ammos->begin (); j != ammos->end (); ++j)
			{
				std::map<std::string, RuleItem*>::const_iterator itItem = ruleItems.find (*j);
				if(itItem == ruleItems.end ())
					continue;
				items[item].push_back(itItem->second);
			}
			break;
		}
		case BT_AMMO:
		default:
			break;
		}
	}

	int row = 0;
	for (std::map<RuleItem*,std::vector<RuleItem*> >::iterator i = items.begin(); i != items.end(); ++i)
	{
		if(!addItems (_game, _lstEquipment, i->first, _base, c, row, _items))
		{
			continue;
		}
		for(std::vector<RuleItem*>::iterator j = i->second.begin (); j != i->second.end (); ++j)
		{
			addItems (_game, _lstEquipment, *j, _base, c, row, _items);
		}
	}

	_timerLeft = new Timer(50);
	_timerLeft->onTimer((StateHandler)&CraftEquipmentState::moveLeft);
	_timerRight = new Timer(50);
	_timerRight->onTimer((StateHandler)&CraftEquipmentState::moveRight);
}

/**
 *
 */
CraftEquipmentState::~CraftEquipmentState()
{
	delete _timerLeft;
	delete _timerRight;
}

/**
 * Runs the arrow timers.
 */
void CraftEquipmentState::think()
{
	State::think();

	_timerLeft->think(this, 0);
	_timerRight->think(this, 0);
}


/**
 * Returns to the previous screen.
 * @param action Pointer to an action.
 */
void CraftEquipmentState::btnOkClick(Action *action)
{
	_game->popState();
}

/**
 * Starts moving the item to the base.
 * @param action Pointer to an action.
 */
void CraftEquipmentState::lstEquipmentLeftArrowPress(Action *action)
{
	_sel = _lstEquipment->getSelectedRow();
	_timerLeft->start();
}

/**
 * Stops moving the item to the base.
 * @param action Pointer to an action.
 */
void CraftEquipmentState::lstEquipmentLeftArrowRelease(Action *action)
{
	_timerLeft->stop();
}

/**
 * Starts moving the item to the craft.
 * @param action Pointer to an action.
 */
void CraftEquipmentState::lstEquipmentRightArrowPress(Action *action)
{
	_sel = _lstEquipment->getSelectedRow();
	_timerRight->start();
}

/**
 * Stops moving the item to the craft.
 * @param action Pointer to an action.
 */
void CraftEquipmentState::lstEquipmentRightArrowRelease(Action *action)
{
	_timerRight->stop();
}

/**
 * Updates the displayed quantities of the
 * selected item on the list.
 */
void CraftEquipmentState::updateQuantity()
{
	Craft *c = _base->getCrafts()->at(_craft);
	std::wstringstream ss, ss2;
	ss << _base->getItems()->getItem(_items[_sel]);
	ss2 << c->getItems()->getItem(_items[_sel]);

	Uint8 color;
	if (c->getItems()->getItem(_items[_sel]) == 0)
	{
		RuleItem *rule = _game->getRuleset()->getItem(_items[_sel]);
		if (rule->getBattleType() == BT_AMMO)
		{
			color = Palette::blockOffset(15)+6;
		}
		else
		{
			color = Palette::blockOffset(13)+10;
		}
	}
	else
	{
		color = Palette::blockOffset(13);
	}
	_lstEquipment->setRowColor(_sel, color);
	_lstEquipment->setCellText(_sel, 1, ss.str());
	_lstEquipment->setCellText(_sel, 2, ss2.str());
}

/**
 * Moves the selected item to the base.
 */
void CraftEquipmentState::moveLeft()
{
	Craft *c = _base->getCrafts()->at(_craft);
	if (c->getItems()->getItem(_items[_sel]) > 0)
	{
		_base->getItems()->addItem(_items[_sel]);
		c->getItems()->removeItem(_items[_sel]);
		updateQuantity();
	}
}

/**
 * Moves the selected item to the craft.
 */
void CraftEquipmentState::moveRight()
{
	Craft *c = _base->getCrafts()->at(_craft);
	if (_base->getItems()->getItem(_items[_sel]) > 0)
	{
		_base->getItems()->removeItem(_items[_sel]);
		c->getItems()->addItem(_items[_sel]);
		updateQuantity();
	}
}

}
