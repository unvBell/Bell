#pragma once

#ifdef _DEBUG

# include <boost/current_function.hpp>

/**
 * �A�T�[�V�����}�N��
 * @param expr expr��false�Ȃ�΃A�T�[�V����
 */
# define BELL_ASSERT(expr)																\
	((void)::bell::detail::assertionCheck(												\
		expr,																			\
		BELL_ASSERTION_FORMAT(#expr, "", __FILE__, __LINE__, BOOST_CURRENT_FUNCTION),	\
		#expr, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION								\
	))


/**
 * ���b�Z�[�W����A�T�[�V�����}�N��
 * @param expr expr��false�Ȃ�΃A�T�[�V����
 * @param msg  �G���[���b�Z�[�W
 */
# define BELL_ASSERT_MSG(expr, msg)														\
	((void)::bell::detail::assertionCheck(												\
		expr,																			\
		BELL_ASSERTION_FORMAT(#expr, msg, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION),	\
		#expr, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION								\
	))

# include "assertion/Assert.hpp"

#else
# define BELL_ASSERT(expr)		((void)0)
# define BELL_ASSERT_MSG(expr)	((void)0)
#endif
