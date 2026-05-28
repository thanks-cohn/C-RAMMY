```text id="d9m4x1"
 ██████╗      ██████╗  █████╗ ███╗   ███╗███╗   ███╗██╗   ██╗
██╔════╝      ██╔══██╗██╔══██╗████╗ ████║████╗ ████║╚██╗ ██╔╝
██║     █████╗██████╔╝███████║██╔████╔██║██╔████╔██║ ╚████╔╝
██║     ╚════╝██╔══██╗██╔══██║██║╚██╔╝██║██║╚██╔╝██║  ╚██╔╝
╚██████╗      ██║  ██║██║  ██║██║ ╚═╝ ██║██║ ╚═╝ ██║   ██║
 ╚═════╝      ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝     ╚═╝   ╚═╝

C-RAMMY

A Fabric-Native Distributed Memory Runtime
Built In C


Machines die.
Memory remains.
The fabric remembers.


GRAND VISION

C-RAMMY is the first evolutionary stage of RAMMY.

The original long-term vision for RAMMY targets Zig as the primary systems
language. However, C-RAMMY exists for one reason:

    BUILD THE ORGANISM FIRST.

Before bare-metal kernels.
Before architecture-specific boot code.
Before distributed operating system replacement.

C-RAMMY focuses on proving the fabric model itself:

    pooled memory
    distributed residency
    process migration
    topology-aware execution
    fault-transparent computation
    distributed AI inference

running today on ordinary Linux systems.


WHAT C-RAMMY IS

C-RAMMY is:

    a distributed memory runtime
    a fabric coordination layer
    a pooled memory system
    a topology-aware execution runtime
    a distributed AI experimentation platform

running on top of Linux.

C-RAMMY is NOT yet:

    a standalone operating system
    a replacement kernel
    a fake cloud orchestrator
    a container platform
    a Kubernetes clone

Linux serves as:

    hardware substrate
    networking layer
    driver layer
    debugging environment
    development cocoon

The fabric logic lives inside C-RAMMY.


WHY C FIRST?

The long-term RAMMY vision still targets Zig.

However, C-RAMMY exists because:

    C has decades of systems examples
    C has massive networking history
    C has mature low-level tooling
    C allows rapid distributed systems prototyping
    C is battle-tested on Linux
    C lowers the barrier to immediate experimentation

The objective is simple:

    PROVE THE MODEL.
    ITERATE RAPIDLY.
    BUILD THE ORGANISM.

Zig remains the long-term architectural direction.

C-RAMMY is the first living prototype.


CORE GOALS

[ ] pooled fabric memory

[ ] distributed page ownership

[ ] distributed process identity

[ ] topology-aware scheduling

[ ] hot/cold page migration

[ ] distributed checkpointing

[ ] failure-transparent execution

[ ] distributed tensor residency

[ ] distributed AI inference

[ ] distributed AI training

[ ] home-lab supercomputing

[ ] fabric-native memory systems


REAL-WORLD TARGETS

[ ] Run a 70B-class LLM across pooled consumer hardware

[ ] Run Stable Diffusion from distributed memory residency

[ ] Build a 1TB+ pooled memory fabric from recycled machines

[ ] Continue AI inference after node failure

[ ] Run distributed scientific workloads entirely from pooled RAM

[ ] Turn ordinary homes and garages into distributed supercomputers


FLAGSHIP DEMONSTRATION TARGET

    5 recycled desktops
    25GbE switch
    pooled memory fabric
    quantized 70B model
    stable token streaming
    live node failover

This demonstrates:

    distributed residency
    pooled memory
    migratory execution
    survivable failure
    topology-aware inference

The objective is not merely distributing jobs.

The objective is making the fabric behave as one machine.


ARCHITECTURE PHILOSOPHY

C-RAMMY intentionally begins as:

    a Linux-hosted distributed runtime

because the first challenge is NOT:

    bootloaders
    SATA drivers
    architecture bring-up

The first challenge is:

    distributed memory civilization

The repository structure reflects this.

The heart of C-RAMMY is:

    fabric/
    gmem/
    runtime/
    coherence/
    ai/
    sim/

The system begins by proving:
    memory can be pooled
    pages can migrate
    processes can survive
    execution can follow topology

Only later does RAMMY evolve toward:

    kernel integration
    hybrid runtime/kernel operation
    bare-metal distributed operating systems


REPOSITORY STRUCTURE

rammy/
├── fabric/
├── gmem/
├── runtime/
├── coherence/
├── ai/
├── sim/
├── tools/
├── tests/
├── kernel/
└── scripts/


INITIAL DEVELOPMENT STRATEGY

PHASE 0:
    Linux-hosted simulation runtime

PHASE 1:
    pooled distributed memory

PHASE 2:
    distributed page ownership

PHASE 3:
    topology-aware migration

PHASE 4:
    distributed AI inference

PHASE 5:
    distributed failover execution

PHASE 6:
    hybrid kernel/runtime integration

PHASE 7:
    fabric-native operating system


INFLUENCES

    Amoeba
    Sprite
    Plan 9
    Kerrighed
    MOSIX
    Distributed NUMA research
    Capability systems
    RDMA fabrics
    TempleOS philosophy
    Transparent systems engineering


FINAL DOCTRINE

A node is an organ.

The fabric is the machine.

Supercomputers are grown,
not purchased.

```
