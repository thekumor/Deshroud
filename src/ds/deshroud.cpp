/* ================================================================
*	
*	Entry point of the app.
*
*	#Authors: The Kumor
*
* ================================================================ */

// Deshroud
#include <ds/application.h>

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	using namespace ds;

	Application app;
	return app.Run();
}