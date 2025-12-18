#pragma once

#ifdef API_ENGINE
	#define MIRA_API __declspec(dllexport)
#else
	#define MIRA_API __declspec(dllimport)
#endif // API_ENGINE


#ifdef _MSC_VER
#pragma warning(disable : 4251 4275 4661)
#endif
