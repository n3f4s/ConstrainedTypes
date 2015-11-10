# ContrainedTypes
Library for defining constrained types (Ada-like constrained types)

This is, for now, a exercise library. I hope it will one day become good enough to be used in real project.

__For now, due to use (for the error handling) of macro defined by g++, this library
may not work on other compiler__

The purpose of this library is to easily create constrained type by composing
types and constraints.
This is done by composing templates types.

For now, constrained are available only for numeric types :
``std::is_arithmetic<T>::value`` must be true for the type.

## How to create a constrained types

To create a constrained type, you just need to create a typedef on the right type.

This *right type* is a composition (with template) of three types :

* ``Numeric_Type<T, Constraint_type> `` on which you add the constraint
* ``Constraint<T, error_function, ...>`` which represent the constraint on the type
* ``Error_Function`` which is a functor use to handle violation of the constraint

``Numeric_Type<T, Constraint_Type>``  take as template parameter : 

* ``T`` : the (arithmetic) type to be constrained
* ``Constraint_Type`` : the constraint on the type.

For exemple : to create a bounded integer with bound as template parameter

```C++
template<int lower_bound, int upper_bound>
using bounded = Numeric_Type<int, Range_Strict<lower_bound, upper_bound, invariant_check>>;
```

and then use it like that :

```C++
bounded<0,10> b1{};
bounded<0,10> b2{9};
```

``Range_Strict`` and ``invariant_check`` are defined in the library

## How to create constraint

To create new constraint, you just need to create a template class (or struct)
that derive from Constraint, has one member function and at least one static member:


```C++
template<typename T, typename error_function>
struct My_Constraint : Constraint<T, error_function>{
    static constexpr bool has_default = /*false or true*/; // tell if the constrained type have
    // a default value
    //static constexpr T default_value = ...; //needed only if has_default is true
    
    void check_invariant( T& value ) const{
        // Your code to check the invariant of the constraint
    }
};
```

for example, to create a Range constraint (not a strict range):

```C++
template<typename T, T lower, T upper, typename error_function>
struct Range : Constraint<T, error_function>{
    static constexpr bool has_default = true;
    static constexpr T default_value = lower;
    
    void check_invariant( T& value ) const{
        auto fun = Constraint<T,error_function>::func
        if(value <= lower) error( lower < value, func );// error is a macro that call the right parameter on func
        if(upper <= value) error( value < upper, func );
    }
};
```

For now, there is an error with error handling : the error handling function takes as parameter
the operation that fail (with ``__FUNCTION*__`` macro) and the condition that did not pass. The ``__FUNCTION__`` is not the right one, and it pass the wrong function name to the error function.

## How to create error handling function

TODO
