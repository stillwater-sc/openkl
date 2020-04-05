/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/Visitors.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/Visitors.hpp#6 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing, Inc. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc.
 */
#ifndef VARIANT_VISITORS_INCLUDED
#define VARIANT_VISITORS_INCLUDED

NS_STILLWATER_AUTOMATION_VISITORS_BEGIN

#ifdef NOW
/**
 * \brief visitor to print two variants
 */
class printPair : public boost::static_visitor<void> {
public:
	template<class T1, class T2>
	void operator()(const T1& lhs, const T2& rhs) const { 
		std::cout << "LHS = " << lhs << " RHS = " << rhs << std::endl;
	}
};

/**
 * \brief visitor to increment a variant with a second
 */
class add : public boost::static_visitor<void> {
public:
	/**
		* \brief add to variants in a visitor pattern
		*/
	template<class T1, class T2>
	void operator()(T1& lhs, const T2& rhs) const { 
		lhs += static_cast<T1>(rhs);
	}

	/**
		* this avoid the problem of unwanted precision loss
		* but doesn't allow us to use different base types
	template<class T>
	void operator()(T& lhs, const T& rhs) const { 
		lhs += rhs;
	}
		*/
};


/**
 * \brief visitor to test if a variant is less than another
 */
class lessThan : public boost::static_visitor<bool> {
public:
	template<class T1, class T2>
	bool operator()(T1& lhs, const T2& rhs) const { return lhs < static_cast<T1>(rhs); }
};

/**
 * \brief visitor to test if a variant is greater than another
 */
class greaterThan : public boost::static_visitor<bool> {
public:
	template<class T1, class T2>
	bool operator()(T1& lhs, const T2& rhs) const { return lhs > static_cast<T1>(rhs); }
};

#endif

NS_STILLWATER_AUTOMATION_VISITORS_END

#endif // VARIANT_VISITORS_INCLUDED
