#pragma once

#ifdef API_ENGINE
	#define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif // DEBUG
