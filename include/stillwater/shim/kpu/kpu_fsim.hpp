#include <iostream>

// STILLWATER headers
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
#include <interfaces/MemoryTypeEnums.hpp>		// ETLO 2/23/07 This is an odd dependency on the namespace definition TODO fix this if you can
// diagnostic services
#define STILLWATER_DIAGNOSTICS
#include <stillwater/diagnostics.hpp>
#include <stillwater/automation.hpp>
// STILLWATER SLM components
#include <stillwater/arch/baseTypes/slmBaseTypes_nsmacro.hpp>
#include <stillwater/arch/baseTypes/Request.hpp>
// STILLWATER Functional model
#include <stillwater/shim/kpu/memory/slm_memory.hpp>

namespace stillwater {
namespace slm {

// Functional model of the KPU
class KpuFsim {
public:
    KpuFsim(size_t memorySize, size_t pageSizeInBytes, size_t nrChannels)
		: _memorySize(memorySize), _nrChannels(nrChannels), _pageSize(pageSizeInBytes) {
		_TOM = _nrChannels * _memorySize;
		for (size_t i = 0; i < nrChannels; ++i) {
			_mem.push_back(std::make_unique<MobMemory>(memorySize, i * memorySize, pageSizeInBytes));
		}
    }

    ~KpuFsim() {
	    // clean up
    }

	void reset() {
		// clear all the memory
	}

	void write(Address baseAddress, const MemoryObject& mob) {
		if (baseAddress < _TOM) {
			// find the channel
			size_t channel = baseAddress / _memorySize;
			_mem[channel]->write(baseAddress % _memorySize, mob);
		}
		else {
			// do we signal the failure?
		}
	}

private:
	size_t      _memorySize;
	size_t		_nrChannels;
	size_t      _pageSize;
	size_t      _TOM;
    std::vector<std::unique_ptr<MobMemory>>   _mem;

};

}  // namespace slm
}  // namespace stillwater

