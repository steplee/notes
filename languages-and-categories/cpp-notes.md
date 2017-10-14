# C++
I need to study up some C++11/14/17 features.

  - Use emplace_back instead of push_back. You can put parameters *directly* in the call! And it's faster, push_back must do a rvalue move (i.e. not a copy, but still a tad slower).

## General STL stuff
[Link](http://www.sgi.com/tech/stl/table_of_contents.html)
  - `iota` assigns increasing values to a range. Mutates
  - Use `copy` with `ostream_iterator` instead of looping over a vector to print: `copy(A, A + N, ostream_iterator<int>(cout, " "));`
  - `partition` puts all things that satisfy a predicate left of things that do not (think quicksort's partition)
```partition(A, A + N,
          compose1(bind2nd(equal_to<int>(), 0),
                   bind2nd(modulus<int>(), 2))); // first do mod2 then equal_to. So expression is i%2==0
```
  - `inner_product`

## Polymorphism
- Subtype polymorphism is also known as runtime polymorphism.
        - The resolution of polymorphic function calls happens at runtime through an indirection via the virtual table.
- Parametric polymorphism is also known as compile-time polymorphism.
        - Ability to execute code for many types.
        - **Templates**
        - C++ -> code bloat
        - (Rampant in Haskell)
- Ad-hoc polymorphism is also known as overloading.
        - Operator overloading
        - *Specialized* templates
        - (Type classes in Haskell)
- Coercion is also known as (implicit or explicit) casting.

## C++11
> C++11 adds a new non-const reference type called an rvalue reference, identified by T&&. This refers to temporaries that are permitted to be modified after they are initialized, for the purpose of allowing "move semantics".

 - `constexpr`
```constexpr int get_five() {return 5;}
int some_value[get_five() + 7]; // Create an array of 12 integers. Valid C++11
```
  - Initializer lists
```void function_name(std::initializer_list<float> list);
function_name({1.0f, -3.45f, -0.4f});
```
  - `decltype`
``` int some_int;
decltype(some_int) other_integer_variable = 5;
```
  - `auto`  
  - Range-based loops when object implements begin/end() iterators
  - `override` after a member definition ensures that you are *actually* overriding a base class function
  - `nullptr`
  - Unordered set and map
  - `shared_ptr unique_ptr`, `auto_ptr` deprecated

```
template<class Lhs, class Rhs>
  auto adding_func(const Lhs &lhs, const Rhs &rhs) -> decltype(lhs+rhs) {return lhs + rhs;}
```

## C++17
  - [Fold expressions (variadic)](http://en.cppreference.com/w/cpp/language/fold)

## Some Boost
#### variant
`boost::recursive_wrapper` — Solves circular dependencies, enabling recursive types.

## Misc.
#### Value, Zero, Default initilization
[Link](http://en.cppreference.com/w/cpp/language/value_initialization)
[Link 2](http://cpptruths.blogspot.com/)

### Functional CPP
[Link](https://functionalcpp.wordpress.com/)

[C++ Template metaprogramming is turing complete, see this for factorial example](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Metafunction)
##### Specialization
```
template<typename T> struct is_void : std::false_type { ... } // normal template instantiaztion
template<> struct is_void<void> : std::true_type      { ... } // specialized
```

Questions I have:
  - How are functions matched against overloaded arguments? Is it all name-mangling?
          - yes it is, compiler looks at function overloads before mangling.
  - What is decltype and '->'.
          - decltype allows you to get the type of another variable at compile-time, e.g. `decltype(foo)` would have whatever type foo does.
          - You can define a function `auto` and use decltype for return type, but the compiler can't determine type until after body, so use `auto (..a..b) {} -> decltype(a+b)`
  - Read up on templates and there representation as instantiated code.
  - Read some stuff on the ABI and calling conventions.
  - Read up on libstd's threading model
  - What are disadvantages of a header only library, besides repetead compilation?
  - Are 'concepts' coming in C++17?
  - what does 'explicit' do?
          - If a constructor has one argument, a second function can take the class and the type of the argument and construct it on-the-fly. *explicit* prevents this.
  - 'static_assert'
  - how to use specified types in templates, i.e. for get<1> etc.
  - I see some code with a templated struct with no memebers but only a typedef?
  - How does boost::variant work.
  - Tagged unions.
  - 'constexpr'
  - move semantics
  - how auto works (hindley-milner?)
  - std::tie
  - 'const' after function declaration in class
          - means that the implicit 'this' pointer is const.

[C++17](https://meetingcpp.com/index.php/br/items/final-features-of-c17.html)
C++ 17:
  - std::variant
    -
  - if constexpr(expression)
          - Essentially allows compile-time branching.o
  - `if` and `switch` and contain variable initilization
  - more copy ellision

## Inversion of Control
#### [Autowiring](http://autowiring.io/)
> provide a declarative way to manage resources through dependency injection. Instead of explicitly instantiating dependencies,
simply declare what you need and Autowiring will manage object creation and wiring.
> A Context is a basic unit of organization in an autowired application. A Context defines the scope in which autowiring resolves dependencies, broadcasts events and filter graph packets, and maintains object and thread lifespans. Contexts form a tree structure. The root of the tree is the global context, which is created automatically. Contexts can "contain" other contexts as child nodes in the context tree. Dependencies within a child context can be satisfied by an autowired member of a parent context (if it can't be satisfied within the child itself).
Most applications will only have a few contexts. Child contexts are most useful when managing temporary resources. For example, if you have multiple views to the same data, the data model could be a type within a parent context while each view exists within a child context. These child contexts could be created and destroyed on demand.
..... The vessel that carries data from one filter to the next is the AutoPacket. An AutoPacket begins life as an “empty” object. The packet is subsequently "decorated" with data.

> in traditional programming, the custom code that expresses the purpose of the program calls into reusable libraries to take care of generic tasks, but with inversion of control, it is the framework that calls into the custom, or task-specific, code.
> A filter graph is used in multimedia processing - for example, to capture video from a webcam. Filters take input, process it (or change the input), and then output the processed data. For example: a video codec takes raw uncompressed video and compresses it using a video standard such as H.264. To compress a multimedia stream a filter graph could have two inputs:
    1. Audio
    2. Video
Usually these are expressed as file sources. The file sources would feed compression filters, the output of the compression filters would feed into a multiplexer that would combine the two inputs and produce a single output. (An example of a multiplexer would be an MPEG transport stream creator.) Finally the multiplexer output feeds into a file sink, which would create a file from the output.
