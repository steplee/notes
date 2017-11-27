# expressjs
MVC
### Setup
### Middleware
Any code that has access to `req` and `res`. Middleware is pipelined. It is a good formalism for non-intrusive libraries.

Middleware has easy support in express:
  1. Declare a middleware: `var mid = function(req,res,next) { /*stuff*/; next(); }`
  2. Call `app.use(mid)`
    - Note: order of middleware is important.

### Static Files
Call `app.use(express.static(path.join(__dirname, 'public')))` to expose assets.
### Routing
### Templating
Engines:
  - egs: very simple, HTML+JS
    - `<%= field =%>` for interpolation
    - can have 'partials' to repeat portions of code
      - use `<% include partials/header %>` to include file `views/partials/header`
    - can have a for loop with `<% arr.forEach( function(field) ...`
      - see docs, you must interleave html+js a lot
    - can have control flow: `<% if(errors) { $> ...`
  - JADE/pug: nice, no closing tags needed

### Forms & Input
In your html: `<form method="POST" action="/<endpoint>">` where endpoint may be e.g. `/users/add`
In the server, catch the post with `app.post(.)` with second arg taking req/res.  The submitted data is inside `res.body`

##### express-validator 
A good validator, usage by middleware.
(Optionally) Configure when registering to app.
After registering, can call `req.checkBody(field,message).<predicate>` where predicate may be `notEmpty()` etc.
Then check for errors with `req.valiationErrors()`.
If there are errors, call `res.render(...)` with the error notification method.
Else, enter to db etc.
### Models & ORM
##### Mongo
npm `mongojs`
### Generator

##### Registering Engine & Views
```
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));
```

### Forms & Input
### Models & ORM
### Generator

### General Notes
#### res
  - `res.send` for general data/text
  - `res.json` for json objects
  - `res.render` for views (when setup)
    - Can take a second argument that the template can bind against

You can set global variables using a middleware with `res`'s `locals`: 
```
app.use(function(req,res,nxt) {
  res.locals.errors = null;
  next();
});
```
