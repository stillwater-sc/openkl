/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/diagnostics/DiagContext.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2010/02/23 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/diagnostics/DiagContext.hpp#6 $
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
#ifndef STILLWATER_DIAG_CONTEXT_INCLUDED
#define STILLWATER_DIAG_CONTEXT_INCLUDED

NS_STILLWATER_DIAGNOSTICS_BEGIN

struct DiagContext : public Context<DiagContext, true> {
	typedef Context<DiagContext, true> parentClass;	// THIS BETTER BE CORRECT in the parameters!
	virtual std::ostream& getStream() { return s; }
	std::string operator*() const { return s.str(); }
	/**
	 * override the FILE/LINE generator to provide
	 * more control over its printing options
	 */
	DiagContext& tag(const char* pFile, int line, const char* pProlog = NULL) {
		return parentClass::tag(pFile, line, pProlog);
	}
private:
	mutable std::ostringstream s;
};

NS_STILLWATER_DIAGNOSTICS_END

#endif // STILLWATER_DIAG_CONTEXT_INCLUDED
