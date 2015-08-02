#pragma once

#include <boost/format.hpp>

namespace bell { namespace detail {
	//	’l
	template <typename Ch, typename Type>
	void formatValue(boost::basic_format<Ch>& f, Type&& val) {
		f % val;
	}

	template <typename Ch>
	void formatValue(boost::basic_format<Ch>& f, bool val) {
		f % boost::io::group(std::boolalpha, val);
	}

	template <typename Ch>
	void formatValue(boost::basic_format<Ch>& f, const Ch* val) {
		constexpr Ch null[] = { Ch{'('}, Ch{'n'}, Ch{'u'}, Ch{'l'}, Ch{'l'}, Ch{'p'}, Ch{'t'}, Ch{'r'}, Ch{')'}, Ch{'\0'} };
		f % (val ? val : null);
	}

	//	ŽÀ‘•
	template <typename Ch, typename... Args>
	void format_impl(boost::basic_format<Ch>& f, Args&&... args) {}

	template <typename Ch, typename Head, typename... Tail>
	void format_impl(boost::basic_format<Ch>& f, Head&& head, Tail&&... tail) {
		formatValue(f, head);
		format_impl(f, tail...);
	}
}}

namespace bell {
	//	format
	template <typename... Args>
	inline std::string format(boost::string_ref fmt, Args&&... args) {
		boost::format f{ fmt.to_string() };
		detail::format_impl(f, args...);
		return f.str();
	}
	
	//	wformat
	template <typename... Args>
	inline std::wstring wformat(boost::wstring_ref fmt, Args&&... args) {
		boost::wformat f{ fmt.to_string() };
		detail::format_impl(f, args...);
		return f.str();
	}
}
