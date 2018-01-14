# [Architectural Styles and the Design of Network-based Software Architectures](https://www.ics.uci.edu/~fielding/pubs/dissertation/top.htm)
Note: I am taking notes on the entire thing, not just REST (part 5.)
The first few chapters are pretty abstract (perhaps too much, eg. precisely defining 'style')

## 1. Software Architecture
 - Architecture is recursively abstractive, bottoming at some nuclear elements.
 - In addition to layers systems also have phases (start-up, loop, shutdown, etc.) where elements serve different purposes. The 'archictecture' encompasses not just the layers but the transitions and operation of the phases.
 - Architecture design =/= Source code structure design.
    - architecture actually independent of monlithic/modular/flat/etc. code base.

> A software architecture is defined by a configuration of architectural elements--components, connectors, and data--constrained in their relationships in order to achieve a desired set of architectural properties.

  - Processing Element = Component: **Transformations of data**
    - Being abstract, it is defined by its interface and services
  - Data Element: **Contain information**
    - Includes data, their representation, and determines whether we serialze+ship or operate remotely, etc.
  - Connecting Element: **Glue pieces together**
    - RPCs, message passing protocols, data streams, etc.
    - May internally be an entire subsystem of components to do transformations/etc, but externally just glues other elements together.
  - Configuration: Structure of relationships. Equivalent to a solution to set of constraints at run time.
    - Property: (looks like a catch-all term for any attribute of architecture)
    - Style: Coordinated set of constraints to restrict roles/features/relationships. Reference.
    - View: Ranking emphasis on components/data/connectors or MVC or other priorites.

## 2. Network App Architecture
  - Distributed systems is transparent, eg. using RPCs
  - Network-based implies all comm. is restricted to message passing. More general.
  - Hard to evaluate architecture.
  - Metrics: 
    - Performance (network & user & efficency)
    - Scalability
    - Simplicity
    - Modifiability (evolvability/extensibility/customizablitiy/configurability/reusability)
    - Visibility (easy monitoring, easy caching)
    - Portability (VMs, containers, programming language, protocols)
    - Reliability (up time, fault tolerance, redundancy)

## 3. Network App Styles
A discussion of different styles (see page for diagrams)

  * Data-flow styles
    - Pipe and Filter
      - read streams and produce streams
      - +: very simple, configurable, reusable
      - -: not efficient, reliable, portable, propagation latency, sequential (not parallelizabble)
    - Uniform Pipe and Filter
      - extra constraint: all components have same interface (eg. Unix stdin/stdout)
      - extra con: performance hit
  * Replication styles
    - Replicated Repository
      - simple replication to decrease load
      - con: maintaining consistency, big data still problematic
    - Cache
      - Variant of RR. Can be local or network-based with `client - stateless server` style.
  * Hierarchical Styles
    - Client-Server
      - cons: constraints, config, efficiency, visibility, coupling
    - Layered System
      - reduce coupling w/ multiple layers
      - examples TCP/IP stack, OSI, hardware interfaces
    - Layered Client-Server
      - add *proxy* and *gateway* components to CS style
      - a proxy acts as shared server for one or mor components, modifiying/forwarding requests
      - a gateway appers as a normal server, but forwards requests to inner-layer servers
      - usually called 'two-tiered', 'three-tiered', 'multi-tiered'
    - Client-Stateless-Server
      - no *session state* on server, kept on client though
      - pros: improve visibility, reliability, scalability
      - cons: network performance hit
    - Client-Cache-Stateless-Server
      - caching enabled by stateless style, not everything can be cached though
    - Layered Client-Cache-Statless-Server
      - eg. DNS
    - Remote Session
      - variant of client-server, light on client: all state on server
      - pros: visibility (100%), simplicity, evovlability
      - cons: scalability
      - example: TELNET
    - Remote Data Access
      - CS that spreads state across client and server
      - example: SQL + RDMS
  * Mobile Code Styles
    - Virtual Machine
      - at base: interpreters. could be virtualization, python, etc.
    - Remote Evaluation
    - Code on Demand
    - LCODC$SS
    - Mobile Agent
    - (Containers, which are not in the report since they are new)
  * Peer-to-Peer
    - Event-based Integration
    - C2
    - Distributed Objects
    - Brokered Distributed Objects
     - example: CORBA

## 4. Desiging the Web Architecture
The WWW is defined by three specs: URI, HTTP, HTML
The WWW lacks a clear architectural style, which is what REST proposes.
## 5. REST
Two approaches to designing an arch.
  1. Start with a blank-state, iteratively add elements until done
  2. Start with all elements and no constraints, apply constraints incrementally

##### Deriving REST
REST is designed by 2.
The **Null style** is empty of all constraints, no boundaries b/t components

###### Adding Constraints
  1. Client-Server
    - seperation of concerns / evolvability / portability
  2. Stateless
    - each request from client must contain all information necessary for server to respond
    - __ALL__ session state on client
    - visibility / reliability / scalability
    - cons: repetitive data, may be inconsistent
  3. Cache
    - must explicitly tag requests cacheable or not
    - cons: may decrease reliability
  4. Uniform Interface
    - > REST is defined by four interface constraints: identification of resources; manipulation of resources through representations; self-descriptive messages; and, hypermedia as the engine of application state.
  5. Layered System
    - to combat overhead+latency inherent to layered systems, add intermediary caches
    - similar to a two-way uniform pipe-and-filter that is dynamic
  6. Code on Demand (optional)
    - clients can download applets and scripts
    - cons: reduce visibility

##### REST Elements
 * Data Elements
   - representations: REST relies on dynamic standards to send b/t nodes
   - nodes should generously tag data with metadata.
   - the key abstraction of all of REST is  **resource**
> A resource is a conceptual mapping to a set of entities, not the entity that corresponds to the mapping at any particular point in time.
  * Connectors
    - various connectors for clients, servers, caches, resolvers, tunnels
    - always stateless. 
  * Components
    - **origin server, gateway, proxy, user agent**
    - gateway is essentially a reverse proxy (CGI, nginx)
    - clinet has control over proxy, but not a gateway
    - user agent is client end-point (browser, app, lynx, etc.)

##### Architectural View
  * Process View
    - uniformity reduces complexity
    - bidirectional
    - services can be hierarchical, without knowledge of inside topology
  * Connector View
    - constraints of generic resource interface
    - protocol not restricted (HTTP, FTP, etc.)
  * Data View
    - dynamic sized messages
    - layered w/ caches
    - representations may be changed b/t layers
    - user wants minimal latency

## 6. Eval


