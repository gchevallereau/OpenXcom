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
#ifndef OPENXCOM_PROJECTILEFLYBSTATE_H
#define OPENXCOM_PROJECTILEFLYBSTATE_H

#include "BattleState.h"
#include "Position.h"
#include "BattlescapeState.h"

namespace OpenXcom
{

class BattlescapeState;
class BattleUnit;
class BattleItem;

class ProjectileFlyBState : public BattleState
{
private:
	BattleUnit *_unit;
	bool validThrowRange();
	BattleItem *_ammo;
	BattleAction _action;
	BattleItem *_projectileItem;
	int _baseAcc;
	int _autoshotCounter;
	int _projectileImpact;
	void createNewProjectile();
	bool _initialized;
public:
	/// Creates a new ProjectileFly class
	ProjectileFlyBState(BattlescapeState *parent, BattleAction action);
	/// Cleans up the ProjectileFly.
	~ProjectileFlyBState();
	/// Initializes the state.
	void init();
	/// Handles a cancels request.
	void cancel();
	/// Runs state functionality every cycle.
	void think();
	/// Get the result of the state.
	std::string getResult() const;

};

}

#endif
