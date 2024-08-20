#include "pch.h"
#include "Helper.h"

__int64 CompIdxToInt(std::pair<unsigned int*, unsigned int*> pair)
{
	return __int64(*pair.first) << 32 | __int64(pair.second);
}
