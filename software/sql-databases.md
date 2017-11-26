# RDMS Implementation

## [From the PostgreSQL docs](https://www.postgresql.org/docs/9.5/static/query-path.html)
>  1. Aconnection from an application program to the PostgreSQL server has to be established. The application program transmits a query to the server and waits to receive the results sent back by the server.
2. The parser stage checks the query transmitted by the application program for correct syntax and creates a query tree.
3. The rewrite system takes the query tree created by the parser stage and looks for any rules (stored in the system catalogs) to apply to the query tree. It performs the transformations given in the rule bodies.
One application of the rewrite system is in the realization of views. Whenever a query against a view (i.e., a virtual table) is made, the rewrite system rewrites the user's query to a query that accesses the base tables given in the view definition instead.
4. The planner/optimizer takes the (rewritten) query tree and creates a query plan that will be the input to the executor.
It does so by first creating all possible paths leading to the same result. For example if there is an index on a relation to be scanned, there are two paths for the scan. One possibility is a simple sequential scan and the other possibility is to use the index. Next the cost for the execution of each path is estimated and the cheapest path is chosen. The cheapest path is expanded into a complete plan that the executor can use.
5. The executor recursively steps through the plan tree and retrieves rows in the way represented by the plan. The executor makes use of the storage system while scanning relations, performs sorts and joins, evaluates qualifications and finally hands back the rows derived.

## [Database System Architecture (Berkley)](http://db.cs.berkeley.edu/papers/fntdb07-architecture.pdf)
> This paper presents an architectural discussion of DBMS design principles, including process models, parallel architecture, storage system design, transaction system implementation, query processor and optimizer architectures, and typical shared components and utilities

Five main components:
  1. Client Communications Manager
    -  Local & Remote
  2. Process Manager
    - Admission Control & Dispatch/Scheduling
  3. Query Processor
  4. Transactional Store Manager
  5. (Shared Components & Utils)

Example of single query-path:
  1. PC establishes connection (2-tier) with CMM
  2. PC sends SQL query, DBMS assigns thread of computation to command. 
  3. Relational Query Processor checks access, compiles SQL to query plan, consisting of operations such as joins, selection, projection, sorting, ...
  4. Before executing, the plan is sent to the TSM (4), where locks on tables are acquired.
  5. 'Unwind the stack', the primitive rows of the query are passed back through the process, e.g. the query executor will select pertient fields, CCM will send to client. Or a cursor will be returned.

### 2. Process Models
OS v. Application LW threads:
  - OS thread context switch
  - LW threads **must** block, so if doing IO, should have OS threads

DBMS worker (thread usually) is 1:1 with DBMS client, think of RPC.

Some simple process models:
  1. process per worker
    - duplicating file handles, context switches, shared-mem data-structures make this unlikely scalable
  2. thread per worker
    - 
  3. process pool

(2.2)

