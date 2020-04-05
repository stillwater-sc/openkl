/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/exceptions.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	30 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #3 $
 * Latest	:	$Date: 2010/09/29 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/exceptions.hpp#3 $
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
#ifndef STILLWATER_EXCEPTIONS_INCLUDED
#define STILLWATER_EXCEPTIONS_INCLUDED

#include <stdexcept>
#include <sstream>
#include <string>

#ifdef REMOVE_EXCEPTIONS
#define TRY
#define CATCH(a) for (std::exception e; false;)
#define CATCH_ALL if(false)
#define THROW
#else
#define TRY try
#define CATCH(a) catch(a)
#define CATCH_ALL catch(...)
#define THROW throw
#endif

// Stillwater base class for contextual macros
#include <stillwater/Context.hpp>

extern std::string getStackTrace();
extern void disableStackTrace();
extern void enableStackTrace();

class ExceptionContext : public Context<ExceptionContext> {
public:
	virtual std::ostream& getStream() { return s; }
	std::string operator*() const { return s.str(); }
protected:
	std::ostringstream s;
};

/** @addtogroup Exceptions
@{ */

#ifdef DISABLE_CHECKS
#pragma message(__FILE__)
#pragma message("PRE/POST-CONDITION CHECKS ARE DISABLED")
#define PRECONDITION(condition) IGNORE_A
#define POSTCONDITION(condition) IGNORE_A
#else
// macro and class to throw an exception on precondition errors
// this will throw when the condition does not hold
#define PRECONDITION(condition) if(condition) ; else throw(precondition_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "PRECONDITION FAILURE(" #condition ")")
struct precondition_error : public std::logic_error {
	explicit precondition_error(const std::string& message) :
	logic_error(message) {}
};

// macro and class to throw an exception on postcondition errors
// this will throw when the condition does not hold
#define POSTCONDITION(condition) if(condition) ; else throw(postcondition_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "POSTCONDITION FAILURE(" #condition ")")
struct postcondition_error : public std::logic_error {
	explicit postcondition_error(const std::string& message) :
	logic_error(message) {}
};

#endif // DISABLE_CHECKS

// macro and class to throw an exception when hitting unimplemented functionality:
//   use this with top-down stub development style
#define THROW_UNIMPLEMENTED(feature) throw(unimplemented_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "UNIMPLEMENTED(" #feature ")")
struct unimplemented_error : public std::runtime_error {
	explicit unimplemented_error(const std::string& message) :
	runtime_error(message) {}
};

// macro and class to throw an exception on fatal errors
#define THROW_FATAL(message) throw(fatal_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "FATAL(" #message ")")
struct fatal_error : public std::runtime_error {
	explicit fatal_error(const std::string& message) :
	runtime_error(message) {}
};

/**
 * specialized exception for memory allocation errors
 */
#define THROW_OUT_OF_MEMORY(message) throw(out_of_memory_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Out Of Memory Error(" #message ")")
struct out_of_memory_error : public std::runtime_error {
	explicit out_of_memory_error(const std::string& message) :
	std::runtime_error(message) {}
};


/*
 * <stdexcept> exceptions wrapped with recursive Context
 */

/**
 * std::logic_error are precondition errors
 */
#define THROW_LOGIC_ERROR(message) throw(std::logic_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Logic Error(" #message ")")
/**
 * std::logic_error specializations
 */
#define THROW_DOMAIN_ERROR(message) throw(std::domain_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Domain Error(" #message ")")
#define THROW_INVALID_ARG(message) throw(std::invalid_argument_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Invalid Agument Error(" #message ")")
#define THROW_LENGTH_ERROR(message) throw(std::length_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Length Error(" #message ")")
#define THROW_OUT_OF_RANGE(message) throw(std::out_of_range)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Out Of Range Error(" #message ")")

/**
 * std::runtime_error are execution errors
 */
#define THROW_RUNTIME_ERROR(message) throw(std::runtime_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Runtime Error(" #message ")")
/**
 * std::runtime_error specializations
 */
#define THROW_RANGE_ERROR(message) throw(std::range_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Range Error(" #message ")")
#define THROW_OVERFLOW_ERROR(message) throw(std::overflow_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Overflow Error(" #message ")")
#define THROW_UNDERFLOW_ERROR(message) throw(std::underflow_error)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "Underflow Error(" #message ")")


/** @) */	//end of doxygen group


#endif // STILLWATER_EXCEPTIONS_INCLUDED
