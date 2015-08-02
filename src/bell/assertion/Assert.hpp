#pragma once

#ifndef BELL_ENABLE_ASSERTION_HANDLER
# include <iostream>
# include "../preprocessor/Stringize.hpp"
#endif


/**
 * �A�T�[�V����������̃t�H�[�}�b�e�B���O
 * @param expr ��������
 * @param msg  �G���[���b�Z�[�W
 * @param file �t�@�C����
 * @param line �s��
 * @param func �֐���
 */
#define BELL_ASSERTION_FORMAT(expr, msg, file, line, func)	\
	"Assertion Failed! " msg "\n"							\
	"assert (" #expr ")\n"									\
	"assert at " file " (" BELL_PP_STRINGIZE(line) ") " func


namespace bell { namespace assertion {
	/**
	 * �A�T�[�V�������
	 */
	struct AssertionInfo {
		const char*	expr;
		const char*	msg;
		const char*	file;
		const long	line;
		const char*	function;
	};


	/**
	 * �A�T�[�V�����̎��s
	 * @param info �A�T�[�V�������
	 */
	void assertionFailed(AssertionInfo info);

#ifndef BELL_ENABLE_ASSERTION_HANDLER
	//	�f�t�H���g�A�T�[�g�n���h��
	inline void assertionFailed(AssertionInfo info) {
		std::cerr << info.msg << std::endl;
		std::abort();
	}
#endif
}}


namespace bell { namespace detail {
	/**
	 * �����̃`�F�b�N
	 * @param cond ����
	 * @param msg  �G���[���b�Z�[�W
	 * @param expr ��������
	 * @param file �t�@�C����
	 * @param line �s��
	 * @param func �֐���
	 */
	constexpr inline bool assertionCheck(bool cond, const char* msg, const char* expr, const char* file, long line, const char* func) {
		return cond ? true : (assertion::assertionFailed({ expr, msg, file, line, func }), false);
	}
}}
