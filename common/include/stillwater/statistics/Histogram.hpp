/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/statistics/Histogram.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #3 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/statistics/Histogram.hpp#3 $
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
#ifndef STILLWATER_HISTOGRAM_INCLUDED
#define STILLWATER_HISTOGRAM_INCLUDED

#include <iostream>
#include <string>
#include <algorithm>

NS_STILLWATER_STATISTICS_BEGIN

/**
	* \brief Histogram is a self-contained histogrammer
	*
	* RESPONSIBILITY
	*	Histogram is responsible for describing histogram data. 
	*
	*	The histogram itself only captures the bin data and bin
	*	description. Otherwise stated, Histogram does not
	*	manage the data array. This design decision was made so
	*	that histograms wouldn't unknowingly grow beyond the 
	*	expectation of the unknowning user.
	*
	* OVERVIEW
	*	For event-based sampling and simulation we need to capture
	*	or drive a workload presented to the system. A quick way
	*	to do this is to use a histogram to find an approximation
	*	of the distribution of the population from which the samples 
	*	were drawn. 
	*
	*	The intended usage of Histogram is for the client to
	*	maintain an STL vector of sample values. Histogram
	*	than provides two types of behavior, fixed and dynamic.
	*	In the fixed histogram mode, the client must install
	*	an a priori binning function. When the client wants to
	*	reduce the data, it calls the analyze method with the sample 
	*	data vector. Histogram will initialize itself and create the
	*	histogram as a function of the binning function.
	*
	*	In the dynamic histogram mode, the client does not have
	*	to provide a binning function. Instead, on the call
	*	to analyze(), the histogram itself figures out what the
	*	best bin size would be and initializes itself accordingly.
	*
	* THEORY OF OPERATION
	*	The bins are described by a minimum, a number of bins, and a
	*	bin size. Histogram	supports automatic histogram creation, 
	*	but is not sufficient to describe irregular histograms 
	*	resulting from coarsening or refinement.
	*/
template<typename Real = double, size_t HISTOGRAM_WIDTH = 80>
class Histogram : public std::vector<int64_t> {
public:
//	constructors
	/**
	 * \brief default constructor
	 */
	Histogram (const std::string& name = "undefined") :
		m_name(name),
		m_k(0),
		m_binSize(0.0),
		m_min(0.0), m_max(0.0), m_average(0.0),
		m_q1(0.0), m_median(0.0), m_q3(0.0),
		m_cumulativeSumOfValues(0.0),
		m_bSumOfValues(false),
		m_bUniformBinSize(true)
	{
		m_binUpperLimits.clear();
		m_binUpperLimits.reserve(32);
		clear();
		reserve(32);
	}
	/**
	 * \brief decorated constructor to fake assignment via a scalar
	 */
	Histogram(int scalar) { *this = 0; }
	
	// \brief copy constructor
	Histogram (const Histogram& rhs) = default;
	Histogram(Histogram&& rhs) = default;

	//	destructor
	~Histogram () {
		m_name.erase();
		m_binUpperLimits.clear();
		clear();
		m_sampleData.clear();
	}

//	operators
	/**
		* \brief assignment operator does a deep copy
		*/
	Histogram&	operator= (const Histogram& rhs) {
		m_name = rhs.m_name;
		m_k = rhs.m_k;
		m_binSize = rhs.m_binSize;
		m_min = rhs.m_min;
		m_q1 = rhs.m_q1;
		m_median = rhs.m_median;
		m_q3 = rhs.m_q3;
		m_max = rhs.m_max;
		m_average = rhs.m_average;
		m_cumulativeSumOfValues = rhs.m_cumulativeSumOfValues;
		m_bSumOfValues = rhs.m_bSumOfValues;
		m_bUniformBinSize = rhs.m_bUniformBinSize;
		if (!m_bUniformBinSize) {
			// copy the bin structure
			m_binUpperLimits.clear();
			for (uint32 i = 0; i < rhs.m_binUpperLimits.size(); i++) {
				m_binUpperLimits.push_back(rhs.m_binUpperLimits[i]);
			}
		}
		// copy the histogram data
		clear();
		for (size_t i = 0; i < rhs.size(); ++i) {
			push_back(rhs[i]);
		}
		// copy the raw sample data
		m_sampleData.clear();
		for (size_t i = 0; i < rhs.m_sampleData.size(); ++i) {
			m_sampleData.push_back(rhs.m_sampleData[i]);
		}
		return *this;
	}
	/**
	 * \brief convenience cast to reset a histogram via a scalar;
	 */
	Histogram&	operator= (const int rhs) {
		m_name.erase();
		m_k = 0;
		m_binSize = 0.0;
		m_min = 0.0;
		m_q1 = 0.0;
		m_median = 0.0;
		m_q3 = 0.0;
		m_max = 0.0;
		m_average = 0.0;
		m_cumulativeSumOfValues = 0.0;
		m_bSumOfValues = false;
		m_bUniformBinSize = true;	// default
		m_binUpperLimits.clear();
		clear();
		return *this;
	}
	/**
		* \brief arithmetic operators
		*/
	Histogram&	operator+= (const Histogram& rhs);

//	modifiers		modifiers can change the state of the object
	/**
	 * \brief reset the complete content of the histogram
	 * This includes the bin structure, the sample data,
	 * and the summary statistics.
	 */
	void	reset () {
		m_k = 0;
		m_binSize = 0;
		m_min = 0;
		m_q1 = 0.0;
		m_median = 0.0;
		m_q3 = 0.0;
		m_max = 0.0;
		m_average = 0.0;
		m_cumulativeSumOfValues = 0.0;
		m_bSumOfValues = false;
		m_bUniformBinSize = true;
		m_binUpperLimits.clear();
		std::vector<int64>::clear();	// base class clear
	}
	/**
		* \brief clear the contents of the histogram
		*/
	void	clearHistogram () {
		std::vector<int64_t>::clear();
	}
	/**
		* \brief assign the histograms name
		*/
	void	setName (const std::string name) { m_name = name; }
	/**
	 * \brief set or reset the integration feature of the histogram.
	 * \param bSumOfValues boolean indicating if you want a frequency histogram or a sumOfValues histogram.
	 */
	void	sumOfValues (const bool bSumOfValues) { m_bSumOfValues = bSumOfValues; };
	/**
	 * \brief set the bin structure of the histogram assuming uniform bins
	 * \param binSize the width of a bin
	 * \param nrOfBins number of bins to use
	 * \param minimum lower bound of the sample data, this defines the base of the histogram.
	 * \param bSumOfValues boolean indicating if you want a frequency histogram or a sumOfValues histogram.
	 * Default is a frequency histogram.
	 *
	 * Create a uniform bin structure for the histogram.
	 * The first bin is defined by the range [minimum, minimum+binSize), 
	 * the second by the range [minimum+binSize, minimum+2*binSize), etc..
	 */
	void setUniformBinStructure (const Real binSize, const uint32_t nrOfBins, const Real minimum, const bool bSumOfValues = false) {
		m_k = nrOfBins;
		m_binSize = binSize;
		m_min = minimum;
		m_bSumOfValues = bSumOfValues;
		//	m_max will be calculated by analyze, as is m_sampleSize
		m_max = minimum;
		m_cumulativeSumOfValues = 0.0;
		// set uniform mode. This boolean modifies the behavior
		// of the BinMap helper method that calculates the bin.
		m_bUniformBinSize = true;
		// clear the data structure for non-uniform bins since we will not be using that
		m_binUpperLimits.clear();

		// preallocate the bins for the sample values
		clear();
		for (uint32 i = 0; i < m_k; i++) {
			push_back(0);
		}
	}
	/**
	 * \brief set the bin structure of the histogram
	 * \param binUpperLimits contains a vector of bin upper limits
	 * \param minimum optional lower bound of the sample data
	 * \param bSumOfValues boolean indicating if you want
	 * a frequency histogram or a sumOfValues histogram 
	 *
	 * Define the bin structure of the histogram. If the bin structure is uniform,
	 * the uniform version of setBinStructure is a better method to use.
	 */
	void setBinStructure (const std::vector<Real>& binUpperLimits, const Real minimum = 0.0, const bool bSumOfValues = false) {
		// copy the bin structure
		m_k = binUpperLimits.size() + 1;
		m_binSize = minimum;
		m_min = minimum;
		m_bSumOfValues = bSumOfValues;
		//	m_max will be calculated by Analyze, as is m_sampleSize
		m_max = minimum;
		m_cumulativeSumOfValues = 0.0;
		// set non-uniform mode. This boolean modifies the behavior
		// of the BinMap helper method that calculates the bin.
		m_bUniformBinSize = false;

		// we manage the bin limits to m_k-1 since the last bin is implicit
		// Since we are using upper limits, the last bin is
		// all values that fell above the last upper limit.
		m_binUpperLimits.clear();
		for (size_t i = 0; i < m_k - 1; ++i) {
			m_binUpperLimits.push_back(binUpperLimits[i]);
		}

		// preallocate the bins for the sample values
		clear();
		for (size_t i = 0; i < m_k; ++i) {
			push_back(0);
		}
	}
	/**
		* \brief create a histogram description
		* \param bAutomatic The histogram can use a user defined bin structure
		* or generate an optimal bin structure based on the data.
		* The parameter bAutomatic controls which algorithms will
		* be used by analyze.
		* \param sampleData the vector sampleData contains the data to
		* be analyzed
		* \param bCumulative controls if the sample data is
		* added to the existing histogram or replacing it
		* \param bRetainSampleData bRetainSampleData controls if the 
		* sampleData is cached inside the Histogram object. 
		* The default is to not caching the sample data.
		*/
	void	analyze (const bool bAutomatic, const std::vector<Real>& sampleData, 
					const bool bCumulative = false, const bool bRetainSampleData = false) {
		// test to see if this is an interesting data set
		if (0 == sampleData.size()) return;	// it was not
		if (true == bAutomatic && true == bCumulative) return; // invalid parameters

		m_cumulativeSumOfValues = 0.0;
		if (!bCumulative) {
			// clear the contents of the value bins
			for (size_t i = 0; i < m_k; ++i) { at(i) = 0; }
		}
		// make a copy of the sample data since we need to sort the samples
		// for numerical accuracy
		std::vector<Real> copyData = sampleData;
		if (bRetainSampleData) {
			// add the retained sample data to the copy
			for (size_t i = 0; i < m_sampleData.size(); ++i) {
				copyData.push_back(m_sampleData[i]);
			}
		}
		// sort the sample vector
		sort(copyData.begin(), copyData.end());

		// now construct the histogram
		if (bAutomatic) {
			// while you are at it, also compute the summary statistics for the data
			m_min = copyData[0];
			m_q1 = copyData[copyData.size() / 4];
			m_median = copyData[copyData.size() / 2];
			m_q3 = copyData[3 * copyData.size() / 4];
			m_max = copyData[copyData.size() - 1];
			m_average = 0.0;
			for (size_t i = 0; i < copyData.size(); i++) {
				m_average += copyData[i];
			}
			m_average /= copyData.size();

			// compute the bin description
			uint64_t k = (uint64_t)floor(1 + 3.322*log((Real)copyData.size()));	// Sturge's Rule
			Real range = copyData.back() - copyData.front();
			Real binSize = (0 == k ? 1 : range / k);
			binSize = (0 == binSize ? 1 : binSize);
			m_binSize = binSize;
			m_k = (uint64_t)(range / binSize) + 1;	// we need the max inclusive bin as well

			// preallocate the bins
			clearHistogram();
			for (size_t i = 0; i < m_k; ++i) { push_back(0); }
			// scan the data set and fill in the histogram
			for (size_t i = 0; i < copyData.size(); ++i) {
				size_t bin = static_cast<size_t>(binMap(copyData[i]));
				// check if we fall outside the last bin, bring it back in if so
				bin = (bin >= static_cast<size_t>(m_k)) ? static_cast<size_t>(m_k - 1) : bin;
				// update histogram frequency information
				if (m_bSumOfValues) {
					at(bin) += static_cast<int64_t>(copyData[i]);
					m_cumulativeSumOfValues += copyData[i];
				}
				else {
					(at(bin))++;
				}
			}
		}
		else {
			// PRECONDITION the bin structure has already been setup
			// 
			// scan the data set and fill in the histogram
			// while you are at it, also compute the summary statistics for the data
			m_q1 = copyData[copyData.size() / 4];
			m_median = copyData[copyData.size() / 2];
			m_q3 = copyData[3 * copyData.size() / 4];
			m_max = copyData[copyData.size() - 1];
			m_average = 0.0;
			for (size_t i = 0; i < copyData.size(); ++i) {
				size_t bin = static_cast<size_t>(binMap(copyData[i]));
				// check if we fall outside the last bin, bring it back in if so
				bin = (bin >= static_cast<size_t>(m_k)) ? static_cast<size_t>(m_k - 1) : bin;
				// update histogram frequency information
				if (m_bSumOfValues) {
					at(bin) += static_cast<int64_t>(copyData[i]);
					m_cumulativeSumOfValues += copyData[i];
				}
				else {
					(at(bin))++;
				}
				m_average += copyData[i];
			}
			m_average /= copyData.size();
		}
		if (bRetainSampleData) {
			// swap the old data with the new
			m_sampleData.clear();
			m_sampleData = copyData;
		}
	}
	/**
	 * \brief normalize the histogram given a min, a max, and a number of bins
	 *
	 * This requires that the histogram has cached its sample data
	 */
	void	normalize (const Real min, const Real max, const uint32_t nrOfBins) {
		setUniformBinStructure((max - min) / nrOfBins, nrOfBins, min);
		analyze(false, m_sampleData, false, false);
	}
	/**
	 * \brief restore a histogram
	 */
	void	restore(std::istream& istr) { istr >> *this; }
	/**
		* \brief merge two histograms
		*
		* Merging histograms is only allowed if they share the same bin structure.
		*/
	void	merge (const Histogram& histo) {
		// test if the bin structures are the same
		if (m_k == histo.m_k &&
			m_binSize == histo.m_binSize	&&
			m_min == histo.m_min) {
			// merge the two histograms
			for (uint32 i = 0; i < m_k; i++) {
				at(i) += histo[i];
			}
		}
		else {
			THROW_RUNTIME_ERROR("Can't merge two histograms with different bin structures");
		}
	}


//	selectors		selectors observe but do not modify the state
//			use const to have the language enforce none-modification
	/**
		* \brief get the name of the histogram
		*/
	std::string	getName () const { return m_name; };
	/**
		* \brief obtain bin size
		*
		* This value is only valid if the histogram uses uniform bin sizes
		*/
	Real		getBinSize () const { return m_binSize; };
	/**
		* \brief obtain sample size
		*/
	size_t		getSampleSize () const { return size(); };
	/**
		* \brief obtain the minimum value of the data represented by this histogram
		*/
	Real		getMin () const { return m_min; };
	/**
		* \brief obtain the first quartile value of the data represented by this histogram
		*/
	Real		getQ1 () const { return m_q1; };
	/**
		* \brief obtain the median value of the data represented by this histogram
		*/
	Real		getMedian () const { return m_median; };
	/**
		* \brief obtain the average value of the data represented by this histogram
		*/
	Real		getAverage () const { return m_average; };
	/**
		* \brief obtain the third quartile value of the data represented by this histogram
		*/
	Real		getQ3 () const { return m_q3; };
	/**
		* \brief obtain the maximum value of the data represented by this histogram
		*/
	Real		getMax () const { return m_max; };
	/**
		* \brief obtain the summary statistics of the underlying data
		*/
	void		getSummaryStats (Real summaryStats[6]) const
	{
		summaryStats[0] = m_min;
		summaryStats[1] = m_q1;
		summaryStats[2] = m_median;
		summaryStats[3] = m_q3;
		summaryStats[4] = m_max;
		summaryStats[5] = m_average;
	}
	/**
		* \brief calculate the minimum value of the histogram data
		*/
	Real		calculateMin () const
	{ 
		Real min = 1.0e100;
		for ( uint32 i = 0; i < size(); i++ ) {
			min = (min < at(i) ? min : at(i));
		}
		return min;
	}
	/**
		* \brief calculate the maximum value of the histogram data
		*/
	Real		calculateMax () const
	{ 
		Real max = 1.0e-100;
		for ( uint32 i = 0; i < size(); i++ ) {
			max = (max > at(i) ? max : at(i));
		}
		return max;
	}
	/**
	 * \brief obtain the cumulative sum of values contained in the histogram
	 *
	 * For sum of value histograms we need the total sum of the values
	 */
	Real		getCumulativeSumOfValues () const { return m_cumulativeSumOfValues; };
	/**
	 * \brief save a histogram object
	 */
	void		save(std::ostream& ostr) const { ostr << *this; }

	/**
	 * \brief state feedback
	 */
	virtual void	print (std::ostream& ostr, const bool bCSV = false) const {
		// print the histogram information
		ostr << "Histogram name   : " << m_name << endl;
		ostr << "Sample size      : " << static_cast<uint64_t>(m_sampleData.size()) << endl;
		ostr << "Number of bins   : " << m_k << endl;
		ostr << "Bin size         : " << m_binSize << endl;
		ostr << "Minimum          : " << m_min << endl;
		ostr << "Maximum          : " << m_max << endl;

		// transform the bin data into a star diagram
		// [min, binsize)         : ****************
		// [binsize, 2*binsize)   : **********
		// [2*binsize, 3*binsize) : *****
		// ...
		// [k-1*binsize, max)     : **
		// [max, infinity)        : ***
		//
		// we have maximally a HISTOGRAM_WIDTH number of '*' per line
		// the maximum number in the bins will have HISTOGRAM_WIDTH number of stars
		Histogram::const_iterator location = std::max_element(begin(), end());
		uint32_t highestFrequency = (uint32_t)(*location);
		Real lowerBound = m_min;
		Real binSize = m_binSize;
		Real upperBound;
		if (m_bUniformBinSize) {
			upperBound = lowerBound + binSize;
		}
		else {
			upperBound = m_binUpperLimits[0];
		}
		printHistogram(ostr, lowerBound, upperBound, binSize, highestFrequency, bCSV);
	}
	/**
	 * \brief Print the histogram in its native form
	 * We are using the parameters lowerBound and upperBound as compute variables.
	 */
	void	printHistogram (std::ostream& ostr, Real lowerBound, Real upperBound, const Real binSize, const uint32_t highestFrequency, const bool bCSV = false) const {
		int64_t value;
		Real proportion;
		size_t i = 0;

		if (0 == size()) return;

		// print the histogram
		while (i < size() - 1) {
			value = at(i);
			if (bCSV) {
				ostr << lowerBound << ", " << upperBound << ", " << (Real)value;
			}
			else {
				ostr << "[" << setprecision(3)
					<< setw(10) << lowerBound << ", "
					<< setw(10) << upperBound << ") : "
					<< setw(10) << (Real)value << " : ";
				// determine the number of proportional stars
				proportion = (Real)value / (Real)highestFrequency;
				for (uint32_t j = (uint32_t)(proportion*HISTOGRAM_WIDTH); j > 0; --j) {
					ostr << "*";
				}
			}
			ostr << endl;
			lowerBound = upperBound;
			if (m_bUniformBinSize) {
				upperBound += binSize;
			}
			else {
				upperBound = m_binUpperLimits[i + 1];
			}
			i++;
		}
		value = at(i);
		if (bCSV) {
			ostr << lowerBound << ", " << upperBound << ", " << (double)value;
		}
		else {
			ostr << "[" << setprecision(3)
				<< setw(10) << lowerBound << ", "
				<< setw(10) << "infini" << ") : "
				<< setw(10) << (Real)value << " : ";
			// determine the number of proportional stars
			proportion = (Real)value / (Real)highestFrequency;
			for (uint32_t j = (uint32_t)(proportion*HISTOGRAM_WIDTH); j > 0; --j) {
				ostr << "*";
			}
		}
		ostr << endl;
	}

protected:
//		member objects
	/**
		* \brief name of the histogram
		*/
	std::string				m_name;
	/**
		* \brief number of bins
		*/
	uint64_t					m_k;
	/**
		* \brief cumulative value of all values in the histogram
		*/
	Real					m_cumulativeSumOfValues;
	/**
		* \brief minimum value in the sample vector used for the histogram
		*/
	Real					m_min;
	/**
		* \brief first quartile value in the sample vector used for the histogram
		*/
	Real					m_q1;
	/**
		* \brief median value in the sample vector used for the histogram
		*/
	Real					m_median;
	/**
		* \brief average value in the sample vector used for the histogram
		*/
	Real					m_average;
	/**
		* \brief third quartile value in the sample vector used for the histogram
		*/
	Real					m_q3;
	/**
		* \brief maximum value in the sample vector used for the histogram
		*/
	Real					m_max;
	/**
		* \brief bin size 
		*/
	Real					m_binSize;
	/**
		* \brief boolean indicating if we create a frequency or an integration histogram
		*
		* In the construction of the histogram (call to Analyze) 
		* we can make a frequency histogram or an integration of values
		* histogram. The latter means that instead of maintaining frequency 
		* information the histogram contains the sum of values for a particular
		* category.
		*/
	bool						m_bSumOfValues;
	/**
		* \brief boolean indicating if we have a uniform or non-uniform bin size structure
		*
		* In automatic mode, the bin size is always uniform.
		* However, the user can set a non-uniform bin structure by providing
		* the vector of bin starts explicitely via a call to SetBinStructure.
		* This boolean only effects the behavior of the helper method
		* BinMap (). BinMap () calculates the bin in which the sample value
		* falls. In uniform mode, this calculation is a simple arithmetic
		* operation. In non-uniform mode, the calculation requires a 
		* search for the proper bin, and is thus significantly slower.
		*/
	bool						m_bUniformBinSize;
	/**
		* \brief bin vector for non-uniform bin size histograms
		*
		* This vector contains the upper limits of each bin.
		*/
	std::vector<Real>			m_binUpperLimits;
	/**
		* \brief raw data backup. 
		*
		* There are situations in which multiple histograms
		* needs to be unified. You need the raw data to be able to do that.
		* If we store the raw data in the histogram object, then we can
		* cut type dependencies between the data source and the histogram.
		* The developer will typically know the size of the data vector
		* and thus can help to determine if locally caching the data is reasonable.
		*/
	std::vector<Real>			m_sampleData;

//	helper functions
	/**
		* \brief bin mapping of a value 
		* This function returns the number
		* of the corresponding bin of the histogram. 
		*/
	uint64_t binMap (const Real value) const {
		if (m_bUniformBinSize) {
			return (uint32_t)((value - m_min) / m_binSize);
		}
		else {
			// linear search the bins for the match
			for (size_t i = 0; i < m_binUpperLimits.size(); ++i) {
				if (value < m_binUpperLimits[i]) {
					return i;
				}
			}
			return m_k;
		}
	}

public:
	/**
		* \brief istream helper to restore protected member variables
		*/
	void			restoreLocalVars (std::istream& istr) {
		istr >> m_name;
		istr >> m_k;
		istr >> m_binSize;
		istr >> m_min;
		istr >> m_max;
		istr >> m_bSumOfValues;
		istr >> m_bUniformBinSize;
		if (!m_bUniformBinSize) {
			m_binUpperLimits.clear();
			int64_t size;
			istr >> size;
			for (int64 i = 0; i < size; i++) {
				real64 value;
				istr >> value;
				m_binUpperLimits.push_back(value);
			}
		}
	}
	/**
		* \brief ostream helper to get to protected member variables
		*/
	void			saveLocalVars (std::ostream& ostr) const {
		ostr << m_name << endl;
		ostr << m_k << endl;
		ostr << m_binSize << endl;
		ostr << m_min << endl;
		ostr << m_max << endl;
		ostr << m_bSumOfValues << endl;
		ostr << m_bUniformBinSize << endl;
		if (!m_bUniformBinSize) {
			ostr << static_cast<uint64>(m_binUpperLimits.size()) << endl;
			for (size_t i = 0; i < m_binUpperLimits.size(); ++i) {
				ostr << m_binUpperLimits[i] << endl;
			}
		}
	}


private:
//		friends
	/**
		* \brief global operators for ostreams
		*/
	template<typename RReal>
	friend std::ostream& operator<< (std::ostream& ostr, const Histogram<RReal>& rhs);
	/**
		* \brief global operators for istreams
		*/
	template<typename RReal>
	friend std::istream& operator>> (std::istream& istr, Histogram<RReal>& rhs);
};

/**
* global stream operators
*/
template<typename Real>
std::ostream& operator<<(std::ostream& ostr, const Histogram<Real>& histogram)
{
	histogram.saveLocalVars(ostr);
	// serialize the vector
	ostr << static_cast<uint64_t>(histogram.size()) << endl;
	for (size_t i = 0; i < histogram.size(); ++i) {
		ostr << (double)histogram[i] << endl;
	}
	return ostr;
}

template<typename Real>
std::istream& operator>>(std::istream& istr, Histogram<Real>& histogram)
{
	histogram.clear();		// clear out current contents
	if (istr.peek() == EOF) return istr;
	histogram.restoreLocalVars(istr);
	if (istr.peek() == EOF) {
		histogram.clear();
		return istr;
	}
	uint32_t nrOfBins;
	istr >> nrOfBins;
	// serialize the vector
	for (uint32_t i = 0; i < nrOfBins; ++i) {
		uint32_t frequency;
		istr >> frequency;
		histogram.push_back(frequency);
	}
	return istr;
}
NS_STILLWATER_STATISTICS_END

#endif // STILLWATER_HISTOGRAM_INCLUDED


