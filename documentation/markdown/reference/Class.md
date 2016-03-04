<p><sup><a href="Bool.md">previous</a> | <a href="Collection.md">next</a></sup></p>

<h1>Class Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Class.h</code></td></tr>
</table>

```c++
class Class;
```

<p><code>flip::Class</code> is a type that represents a declaration of a flip Class. A concrete instance of this class is acquired using an instance of the <a href="../reference/DataModel.md"><code>DataModel</code></a></p>

<h2>Member Functions Synopsys</h2>

<h3>Declaring</h3>

<table><tr><td><code><a href="#member-function-name">name</a></code></td><td>Set the name of the class</td></tr>
<tr><td><code><a href="#member-function-inherit">inherit</a></code></td><td>Inherit from a class</td></tr>
<tr><td><code><a href="#member-function-member">member</a></code></td><td>Declare a member of the class</td></tr>
</table>

<h3>Accessing</h3>

<table><tr><td><code><a href="#member-function-name">name</a></code></td><td>Returns the name of the class</td></tr>
<tr><td><code><a href="#member-function-members">members</a></code></td><td>Returns information on the members of the class</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-name"><code>name</code></h3>
```c++
Class &  name (const char * name_0);
```

<p>Set the name of the class. The name must be in the <code>ascii-7</code> character set, with exception of spaces, control characters as well as <code>del</code> character.</p>

<p>Names starting with <code>flip</code> are reserved.</p>

<p>This function returns a reference to the <code>Class</code> to allow call chaining.</p>

<h3 id="member-function-inherit"><code>inherit</code></h3>
```c++
template <class U>   Class &  inherit ();
```

<p>Inherits from class <code>U</code> passed as a template parameter.</p>

<p>This function returns a reference to the <code>Class</code> to allow call chaining.</p>

<h3 id="member-function-member"><code>member</code></h3>
```c++
template <class U, U T::*ptr_to_member>   Class &  member (const char * name_0);
```

<p>Declare a member of the class. The name must be in the <code>ascii-7</code> character set, with exception of spaces, control characters as well as <code>del</code> character.</p>

<blockquote><h6>W A R N I N G</h6> flip Member declaration must follow the same order as in the C++ class declaration.</blockquote>

<p>This function returns a reference to the <code>Class</code> to allow call chaining.</p>

<h3 id="member-function-name"><code>name</code></h3>
```c++
const char *   name () const
```

<p>Returns the name of the class.</p>

<h3 id="member-function-members"><code>members</code></h3>
```c++
const Members &   members () const
```

<p>Returns information on the members of the class. This allows for automatic introspection of an instance of the class.</p>

<p><sup><a href="Bool.md">previous</a> | <a href="Collection.md">next</a></sup></p>

