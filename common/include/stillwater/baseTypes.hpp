/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/baseTypes.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	2 July 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #10 $
 * Latest	:	$Date: 2010/09/29 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/baseTypes.hpp#10 $
 *
 * Organization:
 *		Stillwater Supercomputing Solutions
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing Solutions. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of 
 * Stillwater Supercomputing Solutions.
 */
#ifndef STILLWATER_BASE_TYPES_INCLUDED
#define STILLWATER_BASE_TYPES_INCLUDED

#include <iostream>
#include <iomanip>

/**
 * Use the BOOST base types and shorten them
 */
#include <cstdint>


typedef uint64_t STILLWATER_HANDLE;

// Binary sizes
const uint64_t SIZE_8		=	         8ll;
const uint64_t SIZE_16		=	        16ll;
const uint64_t SIZE_32		=	        32ll;
const uint64_t SIZE_64		=	        64ll;
const uint64_t SIZE_128		=	       128ll;
const uint64_t SIZE_256		=	       256ll;
const uint64_t SIZE_512		=	       512ll;
const uint64_t SIZE_1K		=	      1024ll;
const uint64_t SIZE_2K		=	      2048ll;
const uint64_t SIZE_4K		=	      4096ll;
const uint64_t SIZE_8K		=	      8192ll;
const uint64_t SIZE_16K		=	     16384ll;
const uint64_t SIZE_32K		=	     32768ll;
const uint64_t SIZE_64K		=	     65536ll;
const uint64_t SIZE_128K	=	    131072ll;
const uint64_t SIZE_256K	=	    262144ll;
const uint64_t SIZE_512K	=	    524288ll;
const uint64_t SIZE_1M		=	   1048576ll;
const uint64_t SIZE_2M		=	   2097152ll;
const uint64_t SIZE_4M		=	   4194304ll;
const uint64_t SIZE_8M		=      8388608ll;
const uint64_t SIZE_16M		=	  16777216ll;
const uint64_t SIZE_32M		=	  33554432ll;
const uint64_t SIZE_64M		=	  67108864ll;
const uint64_t SIZE_128M	=	 134217728ll;
const uint64_t SIZE_256M	=	 268435456ll;
const uint64_t SIZE_512M	=	 536870912ll;
const uint64_t SIZE_1G		=	1073741824ll;
const uint64_t SIZE_2G		=	2147483648ll;
const uint64_t SIZE_3G		=	3221225472ll;
const uint64_t SIZE_4G		=	4294967296ll;
const uint64_t SIZE_5G		=	5368709120ll;
const uint64_t SIZE_6G		=	6442450944ll;
const uint64_t SIZE_7G		=	7516192768ll;
const uint64_t SIZE_8G		=	8589934592ll;

class population {
public:
	/**
	* from : http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive
	* 
	* \brief Counting bits set, in parallel
	* \param count bits set in this (32-bit value)
	* \return total number of bits set in the parameter
	*/
	static int count(uint32_t v) {
		uint32_t c; // store the total here
		const int S[] = {1, 2, 4, 8, 16}; // Magic Binary Numbers
		const int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

		c = v;
		c = v - ((v >> 1) & B[0]);
		c = ((c >> S[1]) & B[1]) + (c & B[1]);
		c = ((c >> S[2]) + c) & B[2];
		c = ((c >> S[3]) + c) & B[3];
		c = ((c >> S[4]) + c) & B[4];
		/* The B array, expressed as binary, is: 
		* B[0] = 0x55555555 = 01010101 01010101 01010101 01010101
		* B[1] = 0x33333333 = 00110011 00110011 00110011 00110011
		* B[2] = 0x0F0F0F0F = 00001111 00001111 00001111 00001111
		* B[3] = 0x00FF00FF = 00000000 11111111 00000000 11111111
		* B[4] = 0x0000FFFF = 00000000 00000000 11111111 11111111

		* We can adjust the method for larger integer sizes by continuing 
		* with the patterns for the Binary Magic Numbers, B and S. 
		* If there are k bits, then we need the arrays S and B to be 
		* ceil(lg(k)) elements long, and we must compute the same number 
		* of expressions for c as S or B are long. 
		* For a 32-bit v, 16 operations are used. 
		*/
		return c;
	}

	static int fastCount(uint32_t v) {
		/*
		* The best bit counting method for 32bit integers takes 
		* only 12 operations, which is the same as the 
		* lookup-table method, but avoids the memory and 
		* potential cache misses of a table. It is a hybrid 
		* between the purely parallel method above and the earlier 
		* methods using multiplies (in the section on counting bits 
		* with 64-bit instructions), though it doesn't use 64-bit 
		* instructions. The counts of bits set in the bytes is 
		* done in parallel, and the sum total of the bits set 
		* in the bytes is computed by multiplying by 0x1010101 
		* and shifting right 24 bits. 
		*/
		uint32_t w = v - ((v >> 1) & 0x55555555);                    // temp
		uint32_t x = (w & 0x33333333) + ((w >> 2) & 0x33333333);     // temp
		uint32_t c = ((x + (x >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
		return c;
	}

	// to account for no bits being set returning 0
	// we must use a 1-based bit offset. So the top
	// most bit set of the value = 0x1 is 1, and
	// the top most bit set of the value = 0x80000000
	// is 31.
	static int topMostBitSet(uint32_t bits) {
		if (bits == 0) return 0;
		int shifts = 0;
		uint32_t mask = 0x80000000;
		while (!((bits & mask) > 0)) {
			mask >>= 1; ++shifts;
		}
		return (31 - shifts);
	}

	static int topMostBitSet64(uint64_t bits) {
		if (bits == 0) return 0;
		uint8_t shifts = 0;
		uint64_t mask = 0x8000000000000000ll;
		while ((bits & mask) > 0) {
			mask >>= 1; ++shifts;
		}
		return (63 - shifts);
	}
};


/**
 * For building symbol tables for enums
 * Define a struct like this:
 * struct YourEnumSymbolTable {
 *		yourEnum	m_value;
 *		const char* m_name;
 * };
 * and then build a symbol table as follows
 * YourEnumSymbolTable YourEnumTable[] = {
 *		ENUM_EXPANDER(YOUR_ENUM_1),
 *		ENUM_EXPANDER(YOUR_ENUM_2),
 *		...
 *		{ 0, NULL}
 * };
 * Then finally, use a lookup like this:
 * while (YourEnumTable[i].m_name) {
 *		if (YourEnumTable[i].m_value == valueToSearch) 
 *			return YourEnumTable[i].m_name;
 *		}
 *	}
 */
#define ENUM_EXPANDER(_enum_) { _enum_, #_enum_ }

/**
 * helpers to enumerate through arrays
 */
template<class T, int size>
char(&ARRAY_SIZE_HELPER(const T (&array)[size]) )[size];
#define ARRAY_SIZE(array) sizeof(ARRAY_SIZE_HELPER(array))

#define NRELEMENTS(array) (sizeof(array)/sizeof(array[0])

/**
 * take a BOOST base type and present it as a textual
 * representation of a binary format.
 *
 * Usage:  ostr << "My bin number " << binint(myBinNumber);
 * output: My bin number 8'b101_0010
 *
 * the class figures out what the width of the representation
 * is and will record that in the prefix
 * using the verilog signal presentation.
 */
class binint {
public:
	/**
	 * construction only through initializing constructors
	 */
	binint(const uint8_t  value)  : m_size(8),m_value(value)  {};
	binint(const uint16_t value) : m_size(16),m_value(value) {};
	binint(const uint32_t value) : m_size(32),m_value(value) {};
	binint(const uint64_t value) : m_size(64),m_value(value) {};

	template<typename T>
	std::ostream& extractor(std::ostream& ostr) const {
		uint8_t maxShift = m_size-1; 
		uint8_t size = m_size;
		ostr << (uint32_t)size << "'b";
		if (m_value == 0) return ostr << "0";
		T value = (T)m_value;
		uint8_t i = 0;
		while (i < size && (value >> maxShift) == 0) { 
			i++; 
			value<<=1; 
		}
		bool bDontLeadWithUnderscore = false;
		if (i%4 == 0) bDontLeadWithUnderscore = true;
		while (i < size) {
			if (bDontLeadWithUnderscore) {
				bDontLeadWithUnderscore = false;
			} else if (i%4==0) {
				ostr << "_";
			}
			ostr << (value >> maxShift); 
			value<<=1; 
			++i; 
		}
		return ostr;
	}
protected:
	/**
	 * storage for the value we hold
	 */
	uint64_t m_value;
	/**
	 * the size we will display
	 */
	uint8_t m_size;

private:
	friend std::ostream& operator<<(std::ostream& ostr, const binint& rhs) {
		switch(rhs.m_size) {
		case 8:
			return rhs.extractor<uint8_t>(ostr);
		case 16:
			return rhs.extractor<uint16_t>(ostr);
		case 32:
			return rhs.extractor<uint32_t>(ostr);
		case 64:
			return rhs.extractor<uint64_t>(ostr);
		default:
			return ostr << "error";
		}
	}

	friend std::istream& operator>>(std::istream& istr, binint& rhs) {
		std::ios_base::fmtflags previousFlagState = istr.flags();
			throw "not implemented yet";
		istr.flags(previousFlagState);
		return istr;
	}

};

/**
 * take a BOOST base integer type and present it as a textual
 * representation of a binary format.
 *
 * Usage:  ostr << "My hex number " << hexint(myBinNumber);
 * output: My hex number 32'xFE_1234
 *
 * the class figures out what the width of the representation
 * is and will record that in the prefix
 * using the verilog signal presentation.
 */
class hexint {
public:
	/**
	 * construction only through initializing constructors
	 */
	hexint(const uint8_t  value)  : m_size(8),m_value(value)  {};
	hexint(const uint16_t value) : m_size(16),m_value(value) {};
	hexint(const uint32_t value) : m_size(32),m_value(value) {};
	hexint(const uint64_t value) : m_size(64),m_value(value) {};

	template<typename T>
	std::ostream& extractor(std::ostream& ostr) const {
		uint8_t maxShift = m_size-4;
		uint8_t size = m_size;
		ostr << (uint32_t)size << "'x";
		if (m_value == 0) {
			ostr << "0";
		}
		else {
			T value = (T)m_value;
			uint8_t i = 0;
			while (i < size && (value >> maxShift) == 0) { 
				i+=4; 
				value<<=4; 
			}
			bool bDontLeadWithUnderscore = false;
			if (i%16 == 0) bDontLeadWithUnderscore = true;
			while (i < size) {
				if (bDontLeadWithUnderscore) {
					bDontLeadWithUnderscore = false;
				} else if (i%16==0) {
					ostr << "_";
				}
				ostr << std::hex << (value >> maxShift); 
				value<<=4; 
				i+=4; 
			}
		}
		return ostr;
	}
protected:
	/**
	 * storage for the value we hold
	 */
	uint64_t m_value;
	/**
	 * the size we will display
	 */
	uint8_t m_size;

private:
	friend std::ostream& operator<<(std::ostream& ostr, const hexint& rhs) {
		std::ios_base::fmtflags previousFlagState = ostr.flags();
		switch(rhs.m_size) {
		case 8:
			rhs.extractor<uint8_t>(ostr);
			break;
		case 16:
			rhs.extractor<uint16_t>(ostr);
			break;
		case 32:
			rhs.extractor<uint32_t>(ostr);
			break;
		case 64:
			rhs.extractor<uint64_t>(ostr);
			break;
		default:
			ostr << "error";
		}
		ostr.flags(previousFlagState);
		return ostr;
	}

	friend std::istream& operator>>(std::istream& istr, hexint& rhs) {
		std::ios_base::fmtflags previousFlagState = istr.flags();
		istr >> std::hex >> rhs.m_value;
		istr.flags(previousFlagState);
		return istr;
	}

};

/**
 * take a byte and create a two character hex string
 * for standard hex dumps
 */
class hexbyte {
public:
	/**
	 * construction only through initializing constructors
	 */
	hexbyte(const char value)  : m_value(value)  {};

protected:
	/**
	 * storage for the value we hold
	 */
	char m_value;

private:
	friend std::ostream& operator<<(std::ostream& ostr, const hexbyte& rhs) {
		std::ios_base::fmtflags previousFlagState = ostr.flags();
		uint32_t nibble0 = rhs.m_value & 0x0f;
		uint32_t nibble1 = (rhs.m_value & 0xf0) >> 4;
		ostr << nibble1 << nibble0;
		ostr.flags(previousFlagState);
		return ostr;
	}

};

/**
 * \brief debug helper to dump the contents of a buffer
 */
inline void dumpBufferInHex(std::ostream& ostr, const char* buffer, uint32_t size) {
	// take 16 bytes and dump it as a 16 character string
	// followed by 16 columns of hex bytes
	uint32_t remainder = size & 0xF;
	uint32_t maxRows = size >> 4;
	uint32_t offset = 0;
	char charStr[17];
	ostr << std::hex;
	for (uint32_t row = 0; row < maxRows; row++) {
		uint32_t c = offset;
		for (int p = 0; p < 16; p++) {
			charStr[p] = ((buffer[c] > 0 && buffer[c] != 0x08) ? buffer[c++] : '.');
		}
		charStr[16] = '\0';
		ostr << charStr << ": ";
		for (int col = 0; col < 16; col++) {
			ostr << hexbyte(buffer[offset++]) << " ";
		}
		ostr << std::endl;
	}
	if (remainder > 0) {
		uint32_t c = offset;
		for (uint32_t p = 0; p < remainder; p++) {
			charStr[p] = ((buffer[c] > 0 && buffer[c] != 0x08) ? buffer[c++] : '.');
		}
		charStr[16] = '\0';
		ostr << charStr << ": ";
		for (uint32_t col = 0; col < remainder; col++) {
			ostr << hexbyte(buffer[offset++]) << " ";
		}
		ostr << std::endl;
	}
	ostr << std::dec;
}

////////////////////////////////////////////////////////////////////////
// Compile time reminder message
// See Windows Developer's Journal, September 1997, pg 45
// Usage
// #pragma Reminder( "This is a reminder" )
//
// Don't use Warning or Error in your reminder message. This will
// cause the IDE to count them as real messages and could stop the
// build process.
//
// The beauty of this macro is that you can double click
// in the output console and be taken to the line that
// needs reminding!
#define Stringize(L) #L
#define MakeString(M,L) M(L)
#define $LINE MakeString( Stringize, __LINE__ )
#define ReminderMsg __FILE__ "(" $LINE ") : Reminder: "
#define Reminder(msg) message( ReminderMsg msg )

////////////////////////////////////////////////////////////////////////
// vector serialization to an ostream
#include <vector>
#include <iterator>	// needed for GCC
template<class T> 
std::ostream& operator<<(std::ostream& ostr, const std::vector<T>& v) {
	copy(v.begin(), v.end(), std::ostream_iterator<T>(ostr, " ")); 
    return ostr;
}

template<class T> 
void shiftDown(std::vector<T>& vectorToShift, const size_t& index) {
	size_t upperBound = vectorToShift.size();
	if (upperBound > index) {
		for (size_t i = index; i < upperBound-1; ++i) {
			vectorToShift[i] = vectorToShift[i+1];
		}
		vectorToShift.pop_back();
	}
}

#include <deque>
template<class T> 
std::ostream& operator<<(std::ostream& ostr, const std::deque<T>& v) {
	copy(v.begin(), v.end(), std::ostream_iterator<T>(ostr, " ")); 
    return ostr;
}

template<class T> 
void shiftDown(std::deque<T>& dequeToShift, const size_t& index) {
	size_t upperBound = dequeToShift.size();
	if (upperBound > index) {
		for (size_t i = index; i < upperBound-1; ++i) {
			dequeToShift[i] = dequeToShift[i+1];
		}
		dequeToShift.pop_back();
	}
}

template<class T> 
void shiftUp(std::deque<T>& dequeToShift, const size_t& index) {
	size_t upperBound = dequeToShift.size();
	if (upperBound > index) {
		for (size_t i = index; i > 0; --i) {
			dequeToShift[i] = dequeToShift[i-1];
		}
		dequeToShift.pop_front();
	}
}
#endif // STILLWATER_BASE_TYPES_INCLUDED
