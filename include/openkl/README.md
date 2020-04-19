# OpenKL protocol

This document describes how the application and the OpenKL environment need to collaborate to
configure and connect a computational environment for the application's algorithms to execute in.


There are three layers of abstraction:

1. application
2. proxy
3. compute target

# Protocol

- application binds to the OpenKL proxy
- application registers remote configuration information to the proxy
- When all remote connections are configured, application asks the proxy to enumerate all the compute targets

After this step the proxy has a database of compute targets it has access to. 

In particular, we are interested in computational systems that leverage workload optimized compute engines.
This could be systems on a chip, this could be distributed systems on a printed circuit board, across
PCBs, or compute engines connected by networks. 

The goal of OpenKL is to remove the distinction between local and remote computes by increasing the
abstraction level of the instruction set of these compute engines to be more application-oriented,
instead of sequential processing oriented.

After the application requests the proxy to enumerate the available compute targets, the application
can now create a computational fabric for its use.

- application queries the proxy for specific compute targets and used that information to model an execution graph that would be beneficial for the execution of the required algorithms
- [application configures the compute targets in an execution graph]

- application allocates data structures and commands on the compute targets

- application orchestrates the computation, pushing data in, triggering execution events, listening for results, restarting computes on failures, etc.

## Synopsis

```
app -> bind to openkl runtime
app -> configures the environment to potentially remote targets
app -> requests that the proxy enumerates all the targets the app has access to
app -> queries the proxy to find specific targets and constructs an execution graph
app -> allocates data structures and command structures
app -> orchestrates execution
```

```
int main(argc, argv) {

   klEnvironment env;

   // configure desired remote execution possibilities
   for (auto tunnel : available_tunnels) {
       env.connect(tunnel);
   }

   // find all targets
   if (!env.enumerate()) {
       ... fail, exit
   }

   // bind the targets the app requires
   for (auto target: available_targets) {
       if (!env.bind(target)) {
           ... fail, exit
       }
   }

   // orchestrate the computation
   ... EXECUTE

   // release the targets the app no longer needs
   for (auto target: bound_targets) {
       if (!env.release(target)) ... report
   }
   
   return EXIT_SUCCESS;
}
```
