/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/ParameterVariant.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/ParameterVariant.hpp#7 $
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
#ifndef PARAMETER_VARIANT_INCLUDED
#define PARAMETER_VARIANT_INCLUDED

#include <iostream>
#include <variant>
NS_STILLWATER_AUTOMATION_BEGIN

/**
 * \brief the data vessel for parameters
 * The nice behavior of the variant is that to get
 * values into the variant you can rely on the basic type
 * casting of values and variables to the closest type in
 * the variant. This creates a situation in which the
 * client program doesn't need to use this 'param' type
 * explicitely. Effectively, you never see this type in
 * the client.
 */
using param = std::variant<int8_t,int16_t,int32_t,int64_t,uint8_t,uint16_t,uint32_t,uint64_t,float,double>;

template<typename Ty>
struct variant_streamer {
	const Ty& val;
};
template<typename Ty> variant_streamer(Ty)->variant_streamer<Ty>;

template<typename Ty>
std::ostream& operator<<(std::ostream& ostr, variant_streamer<Ty> s) {
	return ostr << s.val;
}

template<typename... Tys>
std::ostream& operator<<(std::ostream& ostr, variant_streamer<std::variant<Tys...>> sv) {
	std::visit([&ostr](const auto& v) { ostr << variant_streamer{ v }; }, sv.val);
	return ostr;
}

NS_STILLWATER_AUTOMATION_END

#endif // PARAMETER_VARIANT_INCLUDED
