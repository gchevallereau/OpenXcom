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
 * along with OpenXcom.  If not, see <http:///www.gnu.org/licenses/>.
 */
#ifndef OPENXCOM_GEOSCAPESTATE_H
#define OPENXCOM_GEOSCAPESTATE_H

#include "../Engine/State.h"
#include <vector>

namespace OpenXcom
{

class Surface;
class Globe;
class ImageButton;
class InteractiveSurface;
class Text;
class Timer;

/**
 * Geoscape screen which shows an overview of
 * the world and lets the player manage the game.
 */
class GeoscapeState : public State
{
private:
	Surface *_bg;
	Globe *_globe;
	ImageButton *_btnIntercept, *_btnBases, *_btnGraphs, *_btnUfopaedia, *_btnOptions, *_btnFunding;
	ImageButton *_timeSpeed;
	ImageButton *_btn5Secs, *_btn1Min, *_btn5Mins, *_btn30Mins, *_btn1Hour, *_btn1Day;
	InteractiveSurface *_btnRotateLeft, *_btnRotateRight, *_btnRotateUp, *_btnRotateDown, *_btnZoomIn, *_btnZoomOut;
	Text *_txtHour, *_txtHourSep, *_txtMin, *_txtMinSep, *_txtSec, *_txtWeekday, *_txtDay, *_txtMonth, *_txtYear;
	Timer *_timer;
	bool _pause, _music;
	std::vector<State*> _popups;
public:
	/// Creates the Geoscape state.
	GeoscapeState(Game *game);
	/// Cleans up the Geoscape state.
	~GeoscapeState();
	/// Updates the palette and timer.
	void init();
	/// Runs the timer.
	void think();
	/// Displays the game time/date.
	void timeDisplay();
	/// Advances the game timer.
	void timeAdvance();
	/// Trigger whenever 5 seconds pass.
	void time5Seconds();
	/// Trigger whenever 10 minutes pass.
	void time10Minutes();
	/// Trigger whenever 30 minutes pass.
	void time30Minutes();
	/// Trigger whenever 1 hour passes.
	void time1Hour();
	/// Trigger whenever 1 day passes.
	void time1Day();
	/// Trigger whenever 1 month passes.
	void time1Month();
	/// Resets the timer to minimum speed.
	void timerReset();
	/// Displays a popup window.
	void popup(State *state);
	/// Gets the Geoscape globe.
	Globe *const getGlobe() const;
	/// Handler for clicking the globe.
	void globeClick(Action *action);
	/// Handler for clicking the Intercept button.
	void btnInterceptClick(Action *action);
	/// Handler for clicking the Bases button.
	void btnBasesClick(Action *action);
	/// Handler for clicking the Graph button.
	void btnGraphsClick(Action *action);
	/// Handler for clicking the Ufopaedia button.
	void btnUfopaediaClick(Action *action);
	/// Handler for clicking the Options button.
	void btnOptionsClick(Action *action);
	/// Handler for clicking the Funding button.
	void btnFundingClick(Action *action);
	/// Handler for pressing the Rotate Left arrow.
	void btnRotateLeftPress(Action *action);
	/// Handler for releasing the Rotate Left arrow.
	void btnRotateLeftRelease(Action *action);
	/// Handler for pressing the Rotate Right arrow.
	void btnRotateRightPress(Action *action);
	/// Handler for releasing the Rotate Right arrow.
	void btnRotateRightRelease(Action *action);
	/// Handler for pressing the Rotate Up arrow.
	void btnRotateUpPress(Action *action);
	/// Handler for releasing the Rotate Up arrow.
	void btnRotateUpRelease(Action *action);
	/// Handler for pressing the Rotate Down arrow.
	void btnRotateDownPress(Action *action);
	/// Handler for releasing the Rotate Down arrow.
	void btnRotateDownRelease(Action *action);
	/// Handler for clicking the Zoom In icon.
	void btnZoomInClick(Action *action);
	/// Handler for clicking the Zoom Out icon.
	void btnZoomOutClick(Action *action);
};

}

#endif
