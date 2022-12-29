#pragma once
#include <iostream>
#include <gtest/gtest.h>
#include "crtdbg.h"
using namespace std;
using namespace testing;
namespace testing
{
	class memory_leak_detector : public EmptyTestEventListener
	{
#ifdef _DEBUG
	public:
		virtual void OnTestStart(const TestInfo&);
		virtual void OnTestEnd(const TestInfo& test_info);

	private:
		_CrtMemState _memState;
#endif // _DEBUG
	};
}