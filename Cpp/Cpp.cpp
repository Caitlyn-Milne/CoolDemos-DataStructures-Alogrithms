// Cpp.cpp : Defines the functions for the static library.
//

#include "pch.h"

#include <vector>

#include "framework.h"

// TODO: This is an example of a library function
void fnCpp()
{
	std::vector<int> list;
	{
		int val = 3;
		list.push_back(3);
	}
	int might_break = list[0];
}
