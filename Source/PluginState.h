/*
  ==============================================================================

    PluginState.h
    Created: 14 Apr 2014 3:05:15pm
    Author:  Kykc

  ==============================================================================
*/

#ifndef PLUGINSTATE_H_INCLUDED
#define PLUGINSTATE_H_INCLUDED

#include <vector>

struct AdmvPluginState
{
	AdmvPluginState()
	{
	}

	bool mManualGoniometerScale = false;
	std::pair<double, double> mGoniometerScaleAttackRelease = std::pair<double, double>(0.01, 5000);
	double mManualGoniometerScaleValue = 1.0;
	std::pair<double, double> mSpectrometerMagnitudeScale = std::pair<double, double>(-72., 0.);
};



#endif  // PLUGINSTATE_H_INCLUDED
