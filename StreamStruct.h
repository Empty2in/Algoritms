#ifndef SCOPE_GUARD_H
#define SCOPE_GUARD_H

#include <ios>

namespace myspace {

	class StreamGuard {

	public:
		StreamGuard(std::basic_ios<char>& s);
		~StreamGuard();

	private:
		char fill_;
		std::basic_ios<char>& s_;
		std::streamsize precision_;
		std::basic_ios<char>::fmtflags flags_;
	};

	struct SeparatorIO {
		char sep;
	};
}
#endif

