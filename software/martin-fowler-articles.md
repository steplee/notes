
# [Evolutionary DBs](https://martinfowler.com/articles/evodb.html)
  - Make many small database migrations steps.
  - A typical database alteration process will be like this:
    1. Modify schema
    2. Write database migration script ([see this](http://databaserefactoring.com/index.html))
    3. Change application code
    4. Change database code (views, UDFs, triggers, etc.)
    5. Update indices (if needed)j
    6. Test locally
    7. Commit all changes to VCS
    8. Using continuous integration, globally test and commit if all good.
  - *Agile* methods embrace change, including evolving DBs, while *Waterfall methods* suffer with it.
  - In Agile, design is seen as an on-going process. Iterative development + feedback.

#### Best Practices
 * DBAs closely communicate w/ Developers
 * Artifacts (scripts, tests, diagrams) commited with code into VCS
 * All DB changes are migrations
   - Write them as SQL scripts
   - Assign each an id and track branches
 * Local DB instances
   - It can be very helpful to give devs their own local DB instances to work with.
 * Devs pull DB changes ASAP
   - __pain of integration increases exponenitally with size__
 * Always have data to test DB-accessing code on
 * Transition Phase: a time where DB grandfathers code in (adds complexity though)

# [Dependency Injection](https://martinfowler.com/articles/injection.html)
  - A **Service Locator** is an object that can provide any service a component may need.
  - DI comes at a price of magic, a learning curve, and (if you want full IoC) needing to write/use a framework/library.
  - Service Locator vs Dependency Injection
    - DI: Easy testing
    - SL: More modular
