#pragma once

#define SAFE_RELEASE(p){ if (p){(p)->Release(); (p)=0;} }
#define SAFE_DELETE(p) {if(p) {delete (p); (p)=0;}

__int64 CompIdxToInt(std::pair<unsigned int*, unsigned int> pair);