# Driver and Proxy Architecture

Questions:
- does the proxy also abstract local hardware?
     pros:
	   - one uniform interface
	   - the proxy can be the local resource manager as it is the only sw that connects to the KPU driver
	   - the proxy can handle the distribution of the workload if the local kpu is multi-way
	   - the proxy can be used to deliver value-added services
	            resource utilization
				performance metrics
				remote connection handling
				automatic software updates!!!!
	 cons:
	   - the proxy is more complex than a driver
	   - the proxy has its own life cycle
	   - the proxy creates an additional piece of software
