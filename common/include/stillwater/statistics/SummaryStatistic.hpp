/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/statistics/SummaryStatistic.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/statistics/SummaryStatistic.hpp#4 $
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
 * any form, or disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc.
 */
#ifndef STILLWATER_SUMMARY_STATISTIC_INCLUDED
#define STILLWATER_SUMMARY_STATISTIC_INCLUDED

NS_STILLWATER_STATISTICS_BEGIN

constexpr uint8_t SUMMARY_MIN = 0;
constexpr uint8_t SUMMARY_Q1	= 1;
constexpr uint8_t SUMMARY_Q2	= 2;
constexpr uint8_t SUMMARY_Q3	= 3;
constexpr uint8_t SUMMARY_MAX = 4;

/**
	* \brief SummaryStatistic is a self-contained statistics
	* measurement. It is takes a vector data set to analyze
	* and calculate the summary statistics for.
	*/
template<class Real>
class SummaryStatistic : public std::array<Real,5> {
using const_it = typename std::vector<Real>::const_iterator;
public:
	SummaryStatistic(const std::string& name = "undefined", const std::string& dimension = "unknown") 
		: m_name(name),m_dimension(dimension),m_e1(0.0), m_e2(0.0), m_s(0.0) {
		fill(this->begin(), this->end(), static_cast<T>(0) );
	}
	virtual ~SummaryStatistic() { 
		m_name.erase(); m_dimension.erase();
		fill(this->begin(), this->end(), static_cast<T>(0) );
	}
	// reset the statistics values
	void clear() {	
		fill(this->begin(), this->end(), static_cast<T>(0) );
		m_e1 = m_e2 = m_s = 0;
		// but leave m_name/m_dimension alone
	}
	template<typename Ty>
	void analyze(const std::vector<Ty>& sampleData) {
		std::vector<Ty> copy = sampleData;
		sort(copy.begin(),copy.end());
		this->at(SUMMARY_MIN) = Real(copy[0]);
		this->at(SUMMARY_Q1) = Real(copy[copy.size()/4]);
		this->at(SUMMARY_Q2) = Real(copy[copy.size()/2]);
		this->at(SUMMARY_Q3) = Real(copy[3*copy.size()/4]);
		this->at(SUMMARY_MAX) = Real(copy[copy.size()-1]);
		m_e1 = accumulate(copy.begin(), copy.end(), 0.0)/copy.size();

		// second moment: 1 over N-1 times sum of (x - xbar)^2
		// TODO: figure out how to do this with accumulate()
		m_s	= m_e2 = 0.0;
		if (copy.size () > 1) {
			const_it statIter = copy.begin();
			while (statIter != copy.end ()) {
				m_e2 += (*statIter - m_e1)*(*statIter - m_e1);
				++statIter;
			}
			m_e2 /= (copy.size () - 1);
			m_s = sqrt(m_e2);
		}
		else {
			m_s = m_e2 = 0.0;
		}
	}
	// \brief provide complete summary statistics report
	void summaryStats(std::ostream& ostr) {
		ostr << "Statistic     " << m_name << std::endl;
		ostr << "Dimension     " << m_dimension << std::endl;
		ostr << "Minimum       " << this->at(SUMMARY_MIN) << std::endl;
		ostr << "Q1            " << this->at(SUMMARY_Q1) << std::endl;
		ostr << "Median        " << this->at(SUMMARY_Q2) << std::endl;
		ostr << "Q3            " << this->at(SUMMARY_Q3) << std::endl;
		ostr << "Maximum       " << this->at(SUMMARY_MAX) << std::endl;
		ostr << "Average       " << m_e1 << std::endl;
		ostr << "Second Moment " << m_e2 << std::endl;
		ostr << "Std Deviation " << m_s << std::endl;
	}

public:
	// \brief name of the statistic
	std::string		m_name;
	// \brief dimension descriptor of the statistic
	std::string		m_dimension;
	// first moment
	Real m_e1;
	// second moment
	Real m_e2;
	// standard deviation == sqrt(e2)
	Real m_s;

private:
//		friends
	// \brief global operators for ostreams
	friend std::ostream& operator<< (std::ostream& ostr, const SummaryStatistic<Real>& rhs) {
		return ostr << "Stat: " << std::setw(10) << rhs.m_name << " = " << rhs.m_e1 << "(+-" << rhs.m_s << ") (" << std::setw(10) << rhs.m_dimension << ")";
	}
	// \brief global operators for istreams
	friend std::istream& operator>> (std::istream& istr, SummaryStatistic<Real>& rhs) {
		return istr;
	}
};

NS_STILLWATER_STATISTICS_END

#endif // STILLWATER_SUMMARY_STATISTIC_INCLUDED


