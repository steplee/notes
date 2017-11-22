# Load Balancing
## [Google MAGLEV](https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/44824.pdf)
  - Equal Cost Multipath (EMCP) packet distribution
  - __Consistent Hashing + connection tracking__

A load balancer is composed of several devices between routers and service endpoints. It matches each packet to a corresponding service and forwards it to the serving endpoint.
  - Dedicated hardware is fast but insufficient
    - Can not scale on demand
    - Can not reprogram quickly
    - Are not highly available, they are often deployed in pairs ("1+1 redundancy")
    - Expensive
  - So deploy a distributed software system
    - "N+1 redundancy"
    - Quick changes, scalability, upgrades, ...

A software load balancer is very complex and challenging.
  - Need high throughput
  - Connection persistance
    - packets need to have consistent endpoints.

### Overview
#### Frontend Serving
  - Every Google service has at least one Virtual IP
    - Not assigned to a specific network interface, but served by several service endpoints behind the Maglev facade
    - Maglev maps VIP <-> service endpoints, announces mapping to router via BGP.
    - Router than announces VIP to Google's backbone.
    - Aggregations of VIP networks announced to Internet, global access.
  - Timeline of a browser accessing a Google service:
    1. user types address, browser issues DNS query
    2. DNS response from Google's auth DNS server (cached)
        The DNS server assigns user to nearby frontend (load balanced + geo)
    3. response contains a VIP, browser will attempt connection with it
    4. Router receives VIP packet from user, forwards to Maglev through ECMP
    5. Maglev receives packet, selects endpoint from the set of service endpoints, encapsulates packet with __Generic Routing Encapsulation__ (GRE), with __outer IP__ destined to service endpoint.
    6. Service endpoint will __directly send responses to user__ (Direct Server Retrn, DSR)

*So... how does Maglev maintain connection persistance??*

#### Maglev Config
Each Maglev node contains a **controller and a forwarder**, which learn VIPs to be served from **configuration objects**, which are read from files or sent via RPCs.

Maglev machines poll health status of forwarder and can announce to routers it is broken via BGP.

### Forwarder Design & Implementation
The forwarder is critical for performance.
The forwader:
  1. Receives packets from NIC.
  2. Rewrites them with GRE/IP headers.
  3. Sends back to NIC, which sends them back on network.

steering moduel, hash tables,**consitent hashing table**, **connection tracking table**, transmission queue, ...

#### Speed

#### Consistent Hashing
To address limitations of connection tracking, could share connection state among all Maglev nodes. However this would have a lot of overhead.

Better: use local consistent hashing. A novel new approach "Maglev hashing"


...
