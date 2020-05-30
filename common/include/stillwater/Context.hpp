/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/Context.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	12 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #3 $
 * Latest	:	$Date: 2010/02/23 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/Context.hpp#3 $
 *
 * Organization:
 *		Stillwater Supercomputing Solutions
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing Solutions. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of 
 * Stillwater Supercomputing Solutions.
 */
#ifndef STILLWATER_CONTEXT_INCLUDED
#define STILLWATER_CONTEXT_INCLUDED

/**
 * Variable argument macro/class mechanism that
 * allows assertions to provide extra information
 * about the context of the assertion.
 *
 * This comes from the "Enhancing Asserting" article by
 * Andrei Alexandru in July 2003 C/C++ Users Journal:
 * URL: http://www.ddj.com/dept/cpp/184403745
 *
 */
template <class T, bool bSingleLine = false>
class Context {
public:
	template<typename T2>
	T& print(const char* pName, const T2& value) {
		try {
			if (pName[0]=='"' && pName[std::strlen(pName)-1]=='"') {
				getStream() << "\"" << value << "\"" << separator();
			}
			else {
				getStream() << pName << " = '" << value << "'" << separator();
			}
		} catch(...) {}
		return downcast();
	}
	/**
	 * Provide the opportunity for derived classes
	 * to add a (prefix) tag to the message. This
	 * can speed up searching for the location of
	 * the assert by simply providing FILE/LINE,
	 * but also to prefix an identifier so that
	 * can can GREP for this particular tag to find
	 * messages just for that particular context.
	 */
	T& tag(const char* pFile, int line, const char* pProlog = NULL) {
		try {
			if (pFile) {
				getStream() << leaf(pFile) << "(" << line << ")" << separator();
			} // else don't print filename(linenr) string
			if (pProlog) {
				getStream() << pProlog << separator();
			}
		} catch(...) {}
		return downcast();
	}
	// dummy variables to stop the recursion 
	// of the RECURSE/RECURSE_ pair
	T& CONTEXT_A;
	T& CONTEXT_B;
protected:
	/**
	 * It is essential that you initialize 
	 * CONTEXT_A/B with (*this) so that the
	 * variables above will end the recursion
	 */
	Context() : CONTEXT_A(downcast()), CONTEXT_B(downcast()) {}
	virtual ~Context() {}
	T& downcast() { return static_cast<T&>(*this); }
	static bool singleLine() { return bSingleLine; }
	static const char* separator() { return singleLine() ? "; ": "\n"; }
	static const char* leaf(const char* path) {
		if (!singleLine()) {
			return path;
		}
		else {
			const char* result = path;
			for (const char* p = path; *p; ++p) {
				if (*p=='\\' || *p=='/' || *p==':') {
					result = p+1;
				}
			}
			return result;
		}
		return NULL;
	}
	/**
	 * override getStream if you want to log to a different stream
	 */
	virtual std::ostream& getStream() { return std::cerr; }
private:
	/**
	 * private constructors to avoid direct instantiation
	 */
	Context(const Context& c);
	Context& operator=(const Context& c);
};

#define CREATE_CONTEXT_AND_CONSUME(ContextClass, prolog) \
	ContextClass().tag(__FILE__, __LINE__, prolog).CONTEXT_A

#define CONTEXT_A(expr) print(#expr,expr).CONTEXT_B
#define CONTEXT_B(expr) print(#expr,expr).CONTEXT_A

#endif  // STILLWATER_CONTEXT_INCLUDED


