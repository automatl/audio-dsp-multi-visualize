#ifndef TOMATL_COLOURED_POINT_COLLECTION
#define TOMATL_COLOURED_POINT_COLLECTION

#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"

template <typename T> class GonioPoints
{
public:
	GonioPoints()
	{
		mData = NULL;
		mLength = 0;
		mIndex = 0;
		mSampleRate = 0;
	}

	GonioPoints(std::pair<T, T>* data, size_t length, size_t index, size_t sampleRate)
	{
		mData = data;
		mLength = length;
		mIndex = index;
		mSampleRate = sampleRate;
	}

	std::pair<T, T>* mData;
	size_t mLength;
	size_t mIndex;
	size_t mSampleRate;
};

#endif