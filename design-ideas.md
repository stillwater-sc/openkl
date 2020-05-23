# OpenKL: Virtual Machine for Cloud-Native Supercomputing

one new concept we would like to exploit in OpenKL versus OpenCL is unifying compute resources
into an abstract service.

OpenCL defines a platform as a host with attached compute entities, and OpenCL kernels are functions on
these compute entities.

OpenKL defines an abstract operator interface to decouple the application from the compute
resource, and create an environment in which the compute resource can be fully utilized to
provide service. This includes elastic, scalable, distributed computes, check-pointing/restarts,
and data flow, both fine-grain and coarse-grain. And this resource can be programmed in any
language or run-time that best fits the service.

What the OpenKL environment needs to capture is the attributes of the compute resource so that
either the OpenKL run-time, or the application can map the algorithm onto the compute resource.
So, it is likely that we need some abstract graph machine model to capture compute/communication/memory
constraints at enough detail for an algorithm executor/manager to make good allocation and scheduling
decisions.

# Questions
- what would be the compute resource difference between a remote cluster of cpus and a remote cluster or kpus?
- what does it do a distributed algorithm if you have cpus vs kpus?
- how do we represent a coarse data-flow graph compute resource? Take for example a task-level parallel
program that consists of a series of servers that are configured in a pipeline


## Embedded Targets

| Name	  | Processor Voltage | Operating/Input | CPU Speed | Analog In/Out        | Digital IO/PWM | EEPROM [kB] | SRAM [kB] | Flash [kB] | USB     | UART |
|---------|-------------------|-----------------|-----------|----------------------|----------------|-------------|-----------|------------|---------|------|
| Uno     | ATmega328P        | 5 V / 7-12 V    | 16 MHz    | 6 / 0                | 14/6           | 1           | 2         | 32         | Regular | 1    |
| Zero    | ATSAMD21G18       | 3.3 V / 7-12 V  | 48 MHz    | 6 / 1                | 14/10          | -           | 32        | 256        | 2 Micro | 2    |
| Due     | ATSAM3X8E         | 3.3 V / 7-12 V  | 84 MHz    | 12 / 2               | 54/12          | -           | 96        | 512        | 2 Micro | 4    |
| MKRZero | SAMD21            | 3.3 V           | 48 MHz    | 7 (ADC 8/10/12 bit)/ | 22/12  | -           | 32        | 256        | 1       | 1    |
|         | Cortex-M0+        |                 |           | 1 (DAC 10 bit)       |						
|         | 32bit low power	  |								
|         | ARM MCU			  |						

_Table 1: Arduino resource targets_

---


## Intel Xeon server processors

Intel® Xeon® D processors deliver workload optimized performance in space and power constrained environments, 
from the data center to the intelligent edge. These innovative, system-on-a-chip processors support high-density, 
ingle-socket network, storage, and cloud edge computing solutions with a range of integrated security, network, 
and acceleration capabilities.

Intel® Mesh Architecture in Intel® Xeon® D-2100 processor product family delivers an innovative processor
 architecture enabling performance and efficiency improvements across the broadest variety of usage scenarios 
 and provides the foundation for continued improvements.

New integrated Intel® Advanced Vector Extensions 512 (Intel® AVX-512) bring workload-optimized performance 
and throughput increases for advanced analytics, cryptography and data compression, while the enhanced 
integrated Intel® QuickAssist Technology (Intel® QAT) provides improved security and compression performance 
in cloud, networking, big data, and storage applications—for data in motion and at rest. Now you can 
accelerate compute-intensive operations.
						

| Name	      | Segment | Cores | Threads | Core Freq [MHz] | Peak Freq [MHz] | L3 Cache [MB] | Max Memory [GB] | Memory Type | Memory Freq [MHz] | Nr Memory Channels | PCIe lanes       | USB   | GPIO | UART | TDP [W] |
|-------------|---------|-------|---------|-----------|-----------|---------:|-----------:|-------------|------------:|-----------|------------------|-------|------|------|----:|
| Xeon D-1602 | server  | 2     | 4       | 2500      | 3200      | 3        | 128        | DDR3, DDR4  | 2133        | 2         | 32 PCIe 2.0/3.0  | 8     | yes  | yes  | 27  |
| Xeon D-1622 | server  | 4     | 8       | 2600      | 3200      | 6        | 128        | DDR3, DDR4  | 2133        | 2         | 32 PCIe 2.0/3.0  | 8     | yes  | yes  | 40  |
| Xeon D-1637 | server  | 6     | 12      | 2900      | 3200      | 9        | 128        | DDR3, DDR4  | 2400        | 2         | 32 PCIe 2.0/3.0  | 8     | yes  | yes  | 55  |
| Xeon D-1653 | server  | 8     | 16      | 2800      | 3200      | 12       | 128        | DDR3, DDR4  | 2400        | 2         | 32 PCIe 2.0/3.0  | 8     | yes  | yes  | 65  |

_Table 2: Intel x86 Xeon resource targets_

---

## Stillwater KPU® Domain Flow Architecture® processors

Stillwater KPU processors are distributed data flow engines supporting complex fine-grain parallelism, delivering workload optimized performance in
power and space constrained environments, from embedded processors, the edge and in the cloud data center.

| Product Name   | Segment   | PEs | Threads | Core Freq [MHz] | Peak Freq [MHz] | Cache [MB] | Max Memory [GB] | Memory Type | Memory Freq [MHz] | Memory Channels | PCIe  | USB   | GPIO | UART | TDP [W] |           
|----------------|----------:|----------:|:-------:|----------:|----------:|------:|-----------:|-------------|------------:|----------|-------|-------|------|------|----:|
| KPU T-64x8     | sensor    | 64        | 8       | 100       | 500       | 0     | 1          | DDR3,DDR4   | 1200        | 1        | 32    | 4     | yes  | no   | 5   |
| KPU T-256x8    | embedded  | 256       | 8       | 200       | 500       | 1     | 2          | DDR3,DDR4   | 1200        | 1        | 32    | 4     | yes  | no   | 25  |
| KPU T-1024x8   | edge      | 1024      | 8       | 500       | 500       | 2     | 4          | DDR3,DDR4   | 1200        | 1        | 32    | 4     | yes  | no   | 75  |
| KPU T-4096x8   | server    | 4096      | 8       | 500       | 500       | 4     | 16         | DDR3,DDR4   | 1200        | 2        | 32    | 4     | yes  | no   | 150 |
| KPU T-16kx32   | cloud     | 16384     | 32      | 500       | 500       | 8     | 16         | DDR3,DDR4   | 1200        | 4        | 32    | 4     | yes  | no   | 300 |

_Table 3: Stillwater KPU resource targets_

---

It is clear that we need a metric of compute performance and capacity to unify the spectrum of compute resources.
It is likely that we need to run a characterization at the workload (algorithm) level to empirically categorize
compute resources into something that quickly identifies if they are competitive in a list of compute resources
OpenKL would provide to the run-time.

Furthermore, the interface attributes are also interesting to capture, so that you could dispatch smart sensor 
and actuator codes. So the UART, GPIO, Analog I/O, and Digital I/O, and higher level protocol pins such as
USB, and PCIe are valuable as well.