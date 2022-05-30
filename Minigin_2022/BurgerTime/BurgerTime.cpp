// BurgerTime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "BurgerTimePCH.h"

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BurgerTimeGame.h"
#include "Minigin.h"

int main(int, char* []) {
	BurgerTimeGame engine;
	engine.Run();
	return 0;
}

