#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Exception.hpp"

using namespace std;
using namespace bell::exception;

TEST(Bell_Exception, Throw) {
	EXPECT_THROW(BELL_THROW(Exception<exception>, "a"), exception			);
	EXPECT_THROW(BELL_THROW(Exception<exception>, "a"), Exception<exception>);
	EXPECT_THROW(BELL_THROW(Exception<exception>, "a"), ErrorInfoRecorder	);
	
	EXPECT_THROW(BELL_THROW(Exception<runtime_error>, "b", nullptr), exception					);
	EXPECT_THROW(BELL_THROW(Exception<runtime_error>, "b", nullptr), runtime_error				);
	EXPECT_THROW(BELL_THROW(Exception<runtime_error>, "b", nullptr), Exception<runtime_error>	);
	EXPECT_THROW(BELL_THROW(Exception<runtime_error>, "b", nullptr), ErrorInfoRecorder			);
}

TEST(Bell_Exception, Rethrow) {
	try {
		BELL_THROW(Exception<exception>, "a");
	}
	catch(ErrorInfoRecorder& e) {
		EXPECT_THROW(BELL_RETHROW(e), exception				);
		EXPECT_THROW(BELL_RETHROW(e), Exception<exception>	);
		EXPECT_THROW(BELL_RETHROW(e), ErrorInfoRecorder		);
	}
	
	try {
		BELL_THROW(Exception<runtime_error>, "b", nullptr);
	}
	catch(ErrorInfoRecorder& e) {
		EXPECT_THROW(BELL_RETHROW(e), exception					);
		EXPECT_THROW(BELL_RETHROW(e), runtime_error				);
		EXPECT_THROW(BELL_RETHROW(e), Exception<runtime_error>	);
		EXPECT_THROW(BELL_RETHROW(e), ErrorInfoRecorder			);
	}
}

#endif
