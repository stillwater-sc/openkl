/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/ParameterFactory.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/ParameterFactory.hpp#7 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of
 * Stillwater Supercomputing, Inc. It may not be copied or duplicated in
 * any form, or  disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc.
 */
#ifndef PARAMETER_FACTORY_INCLUDED
#define PARAMETER_FACTORY_INCLUDED

NS_STILLWATER_AUTOMATION_KNOBS_BEGIN

// forward reference
class Parameter;

/**
 * \brief a factory for Parameter objects
 */
class ParameterFactory {
public:
	static Parameter* createParameter(const std::string& name, const std::string& dimension, const std::string& instanceName,
			const param& min, 
			const param& nominal, 
			const param& max, 
			const param& step) 
	{
		return new Parameter(name, dimension, instanceName, min, nominal, max, step);
	}
private:
	/**
	* \brief private constructor since this object is
	* not intended to be constructed.
	*/
	ParameterFactory() {};
};

/** 
* \brief access macro to instantiate Parameters
*/
#define DYNAMIC_PARAM stillwater::automation::knobs::ParameterFactory::createParameter

/**
* \brief maximum size of parameter names
*/
#define MAX_PARAMETER_NAME_SIZE 512

NS_STILLWATER_AUTOMATION_KNOBS_END

#endif // PARAMETER_FACTORY_INCLUDED


