#include "ApplicationRenderer.h"

int main()
{
	ApplicationRenderer application;
	application.WindowInitialize(2020, 1180);
	application.Render();
	return 0;
}