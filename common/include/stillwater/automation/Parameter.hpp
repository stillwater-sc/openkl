/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/Parameter.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #9 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/Parameter.hpp#9 $
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
#ifndef PARAMETER_INCLUDED
#define PARAMETER_INCLUDED

#include <variant>

NS_STILLWATER_AUTOMATION_KNOBS_BEGIN

/**
 * \brief a range to be used for enumeration
 */
struct ParameterRange {
	ParameterRange(const std::string& name, const param& min, const param& max)
		: m_name(name), m_min(min), m_max(max) {}
	std::string getName() const { return m_name; }
	std::string m_name;
	param m_min, m_max;
private:
	friend std::ostream& operator<<(std::ostream& ostr, const ParameterRange& rhs) {
		return ostr << rhs.m_name << "[" 
			<< variant_streamer{ rhs.m_min }
			<< "," 
			<< variant_streamer{ rhs.m_max }
			<< "]";
	}
};

// forward reference
class ParameterSet;

/**
 * \brief the basic Parameter holding the range, current value, and descriptive information
 * The Parameter denotes a control variable. Both control variables
 * and response variables are separated into their own right space
 * so that other software can interrogate and control their behavior.
 * 
 */
class Parameter	{
public:
	using SharedPointer = std::shared_ptr<Parameter> ;
	/**
	 * \brief default constructor sets up a parameter, its valid range, and dimension
	 */
	Parameter(const std::string& instanceName, const std::string& name, const std::string& dimension, 
				const param& min, const param& nominal, const param& max, 
				const param& step);
	Parameter(const std::string& instanceName, const std::string& name, const std::string& dimension);
	/**
	 * \brief virtual destructor
	 *
	 * If we remove an Parameter object of any kind, we need
	 * to make certain that we remove it from the ParameterSet
	 * as well so that that set is pointing to valid Parameter
	 */			
	~Parameter();

	// modifiers
	void configure(const param& min, const param& nominal, const param& max, const param& step) {
		m_current	= nominal;
		m_min		= min;
		m_nominal	= nominal;
		m_max		= max;
		m_step		= step;
	}
	void setName(const std::string& instanceName, const std::string& name) { m_instanceName = instanceName; m_name = name; }
	void setDimension(const std::string& dimension) { m_dimension = dimension; }
	void reset() { m_current = m_nominal; }
	void setMin() { m_current = m_min; }
	void setMax() { m_current = m_max; }
	void setNominal() { m_current = m_nominal; }
	void setCurrent(const param& newCurrent) { m_current = newCurrent; }
	void setStep(const param& step) { m_step = step; }
	bool step() {
		param nextValue = std::visit([](auto&& arg1, auto&& arg2) -> param {return arg1 + arg2; }, m_current, m_step);

		bool inRange = std::visit([](auto&& arg, auto&& upperlimit) -> bool { 
			using T = std::decay_t<decltype(arg)>;
			return arg < T(upperlimit); 
		}, nextValue, m_max);
		if (inRange) {
			setCurrent(nextValue);
			return true;
		}
		return false;
	}

	// selectors, use const to enforce non-modification
	std::string getName() const { return m_name; }
	std::string getDimension() const { return m_dimension; }
	std::string getInstanceName() const { return m_instanceName; }
	std::string getQualifiedName() const { return m_instanceName + std::string("::") + m_name; }
	param getMin() const { return m_min; }
	param getMax() const { return m_max; }
	param getNominal() const { return m_nominal; }
	param getCurrent() const { return m_current; }

protected:
	// member variables
	/**
	 * name of the parameter. This is a simple string so
	 * that you can layer hierarchy on the set of parameters
	 * if you need to
	 */
	std::string	m_name;
	/**
	 * \brief description of the dimension of this parameter
	 * Mostly used for human understanding of this parameter
	 */
	std::string	m_dimension;
	/**
	 * \brief description of the instance name to which this parameter belongs
	 * Since there can be many objects that want to name 
	 * a parameter with a common name such as "clkPeriod",
	 * we need a mechanism to disambiguate the parameters.
	 * This variable provides a prefix naming option to 
	 * allocate a particular parameter name to a specific
	 * named object instance.
	 */
	std::string	m_instanceName;
	/**
	 * \brief the range of the parameter
	 */
	param		m_min, m_nominal, m_max;
	/**
	 * \brief the current value of the parameter
	 */
	param		m_current;
	/**
	 * \brief the increment to use for enumeration
	 */
	param		m_step;

private:
	/**
	 * \brief global ostream operator
	 */
	friend std::ostream& operator<<(std::ostream& ostr, const Parameter& rhs);
	friend std::ostream& operator<<(std::ostream& ostr, const Parameter* rhs);
};

NS_STILLWATER_AUTOMATION_KNOBS_END

#endif // PARAMETER_INCLUDED
