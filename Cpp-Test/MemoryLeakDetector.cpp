#include "pch.h"
#include "MemoryLeakDetector.h"

//thanks to https://github.com/stbrenner/gtest_mem.git
using namespace std;
using namespace testing;

namespace testing
{
	void memory_leak_detector::OnTestStart(const TestInfo&)
	{
		_CrtMemCheckpoint(&_memState);
	}

	void memory_leak_detector::OnTestEnd(const TestInfo& test_info)
	{
		if (test_info.result()->Failed()) return;
		_CrtMemState now, dif;
		_CrtMemCheckpoint(&now);
		const int diff_result = _CrtMemDifference(&dif, &_memState, &now);
		if (diff_result > 0)
		{
			FAIL() << "Memory leak of " << dif.lSizes[1] << " byte(s) detected.";
		}
	}
}

GTEST_API_ int main(int argc, char** argv)
{
	InitGoogleTest(&argc, argv);
	UnitTest::GetInstance()->listeners().Append(new memory_leak_detector());
	return RUN_ALL_TESTS();
}
