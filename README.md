Inferno® is a distributed operating system, originally developed at Bell Labs, but now developed and maintained by Vita Nuova® as Free Software.  Applications written in Inferno's concurrent programming language, Limbo, are compiled to its portable virtual machine code (Dis), to run anywhere on a network in the portable environment that Inferno provides.  Unusually, that environment looks and acts like a complete operating system.

The use of a high-level language and virtual machine is sensible but mundane. The interesting thing is the system's representation of services and resources.  They are represented in a file-like name hiearchy.  Programs access them using only the file operations open, read/write, and close.  The 'files' may of course represent stored data, but may also be devices, network and protocol interfaces, dynamic data sources, and services.  The approach unifies and provides basic naming, structuring, and access control mechanisms for all system resources.  A single file-service protocol (the same as Plan 9's 9P) makes all those resources available for import or export throughout the network in a uniform way, independent of location. An application simply attaches the resources it needs to its own per-process name hierarchy ('name space').

The system can be used to build portable client and server applications. It makes it straightforward to build lean applications that share all manner of resources over a network, without the cruft of much of the 'Grid' software one sees.

Inferno can run 'native' on various ARM, PowerPC, SPARC and x86 platforms but also 'hosted', under an existing operating system (including AIX, FreeBSD, Irix, Linux, MacOS X, Plan 9, and Solaris), again on various processor types.

This project includes source for the basic applications, Inferno itself (hosted and native), all supporting software, including the native compiler suite, essential executables and supporting files.

How this fork differs: the focus is on using limbo as a programming language on 64bit hosts: amd64, arm64, risc64. Development will be on getting the JIT working well and language binding for popular libraries such as SQLite. 

To build the repo, install the package dependencies on Linux
```
$ apt install libx11-dev libxext-dev linux-libc-dev
```

Then in the root folder of the repo,
```
$ export ROOT=<path to inferno>
$ export objtype=amd64
$ export PATH=$PATH:$ROOT/Linux/$objtype/bin
$ ./makemk.sh
$ mk mkdirs
$ mk install
```
That will bind all the binaries for mk, iyacc, limbo, and emu in Linux/amd64/bin and also build all the dis object code. Inferno can then be launched by just typing `emu`.

```
$ emu
; wm/wm&
```

