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
#ifndef OPENXCOM_SOLDIER_H
#define OPENXCOM_SOLDIER_H

#include <string>
#include "yaml.h"
#include "Unit.h"

namespace OpenXcom
{

enum SoldierRank { RANK_ROOKIE, RANK_SQUADDIE, RANK_SERGEANT, RANK_CAPTAIN, RANK_COLONEL, RANK_COMMANDER};
enum SoldierGender { GENDER_MALE, GENDER_FEMALE };
enum SoldierLook { LOOK_BLONDE, LOOK_BROWNHAIR, LOOK_ORIENTAL, LOOK_AFRICAN };

class Craft;
class SoldierNamePool;
class RuleSoldier;

/**
 * Represents a soldier hired by the player.
 * Soldiers have a wide variety of stats that affect
 * their performance during battles.
 */
class Soldier : public Unit
{
private:
	std::wstring _name;
	int _id;
	RuleSoldier *_rules;
	UnitStats _initialStats, _currentStats;
	SoldierRank _rank;
	Craft *_craft;
	SoldierGender _gender;
	SoldierLook _look;
	int _missions, _kills;
	bool _recentlyPromoted;
public:
	/// Creates a new soldier.
	Soldier(RuleSoldier *rules, RuleArmor *armor);
	/// Creates a new soldier with random stats.
	Soldier(RuleSoldier *rules, RuleArmor *armor, const std::vector<SoldierNamePool*> *names, int *id);
	/// Cleans up the soldier.
	~Soldier();
	/// Initialises
	void initStatsIncrease();
	/// Loads the soldier from YAML.
	void load(const YAML::Node& node);
	/// Saves the soldier to YAML.
	void save(YAML::Emitter& out) const;
	/// Gets the soldier's name.
	std::wstring getName(Language *lang = 0) const;
	/// Sets the soldier's name.
	void setName(const std::wstring &name);
	/// Gets the soldier's craft.
	Craft *const getCraft() const;
	/// Sets the soldier's craft.
	void setCraft(Craft *craft);
	/// Gets a string version of the soldier's rank.
	std::string getRankString() const;
	/// Gets a sprite version of the soldier's rank.
	int getRankSprite() const;
	/// Gets the soldier's rank.
	SoldierRank getRank() const;
	/// Increase the soldier's military rank.
	void promoteRank();
	/// Gets the soldier's time units.
	int getTimeUnits() const;
	/// Gets the soldier's stamina.
	int getStamina() const;
	/// Gets the soldier's health.
	int getHealth() const;
	/// Gets the soldier's bravery.
	int getBravery() const;
	/// Gets the soldier's reactions.
	int getReactions() const;
	/// Gets the soldier's firing accuracy.
	int getFiringAccuracy() const;
	/// Gets the soldier's throwing accuracy.
	int getThrowingAccuracy() const;
	/// Gets the soldier's melee accuracy.
	int getMeleeAccuracy() const;
	/// Gets the soldier's strength.
	int getStrength() const;
	/// Gets the soldier's missions.
	int getMissions() const;
	/// Gets the soldier's kills.
	int getKills() const;
	/// Gets the soldier's gender.
	SoldierGender getGender() const;
	/// Gets the soldier's look.
	SoldierLook getLook() const;
	/// Gets a string version of the soldier's armor.
	std::string getArmor() const;
	/// Gets soldier rules.
	RuleSoldier *getRules() const;
	/// Gets the soldier's stand height.
	int getStandHeight() const;
	/// Gets the soldier's kneel height.
	int getKneelHeight() const;
	/// Gets the soldier's loft ID.
	int getLoftemps() const;
	/// Gets the soldier's value.
	int getValue() const;
	/// Gets the soldier's unique ID.
	int getId() const;
	/// Add a mission to the counter.
	void addMissionCount();
	/// Add a kill to the counter.
	void addKillCount();
	/// Get pointer to current stats.
	UnitStats *getCurrentStats();

};

}

#endif
