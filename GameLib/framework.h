#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dxgi1_4.h>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <deque>
#include <typeinfo>
#include <array>

#pragma comment(lib, "d2d1.lib")
#pragma	comment(lib, "dwrite.lib")
#pragma	comment(lib, "windowscodecs.lib")
#pragma	comment(lib, "dxgi.lib")