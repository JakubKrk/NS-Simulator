#pragma once
#include <string>

using Group = std::size_t;

static enum groupLabels : std::size_t
{
	groupGraphs,
	groupBackground,
	groupPlots,
	groupWallVertical,
	groupWallHorizontal,
	groupFood,
	groupBlobsActive,
	groupBlobsInactive,
	groupFoodInactive,

};