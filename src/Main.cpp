#include <iostream>
#include <Windows.h>
#include <gtest/gtest.h>

#ifdef _DEBUG
#  pragma comment(lib, "gtest/gtest_d.lib")
#endif

//	エントリーポイント
int main(int argc, char* argv[]) {
	using namespace std;

	//	メモリリークのチェック
#if defined(_DEBUG) && defined(_MSC_VER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try {
		//	単体テスト
#ifdef _DEBUG
		testing::InitGoogleTest(&argc, argv);
		if(int result = RUN_ALL_TESTS())
			return result;
#endif
	}
	catch(const exception& e) {
		cerr << "Error! Exception"	<< endl;
		cerr << typeid(e).name()	<< endl;
		cerr << e.what()			<< endl;
	}
	catch(...) {
		cerr << "Error! Unknown exception" << endl;
	}

	return 0;
}
