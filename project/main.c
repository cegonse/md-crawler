#include <genesis.h>

#include "system.h"

int main()
{
	u8 detected_controllers;

	System_Init(&detected_controllers);

	while (1)
	{
		System_EndFrame();
	}

	return (0);
}
