<p><sup><a href="Bool.md">previous</a> | <a href="Collection.md">next</a></sup></p>

<h1>Class Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Class.h</code></td></tr>
</table>

```c++
template <class T> class Class;
```

<p><code>flip::Class</code> is a type that represents a declaration of a flip Class. A concrete instance of this class is acquired using an instance of the <a href="../reference/DataModel.md"><code>DataModel</code></a></p>

<h2>Template Parameters</h2>

<table><tr><td><code>T</code></td><td>The type to declare. <code>T</code> must inherit from <code>flip::Object</code></td></tr>
</table>

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

<p>Example :</p>

```c++
class Model : public DataModel <Model> {};

class Root : public Object
{
public:
   Int   value;
};

auto & root_class = Model::declare <Root> ();
// 'root_class' is of type 'Class <Root>'

root_class
   .name ("myapp.Root")
   .member <Int, &Root::value> ("value");
```

<h3 id="member-function-inherit"><code>inherit</code></h3>
```c++
template <class U>   Class &  inherit ();
```

<p>Inherits from class <code>U</code> passed as a template parameter. Multiple inheritance is not supported.</p>

<p>This function returns a reference to the <code>Class</code> to allow call chaining.</p>

<p>Example :</p>

```c++
class Model : public DataModel <Model> {};

class A : public Object
{
public:
   Int   value;
};

class B : public A
{
public:
   Float value2;
};

// first declare base class
Model::declare <A> ()
   .name ("myapp.A")
   .member <Int, &A::value> ("value");

// then declare inherited classes
Model::declare <B> ()
   .name ("myapp.B")
   .inherit <A> ()
   .member <Float, &B::value2> ("value2");
```

<p>Inheriting imports all members of superclass in the class, therefore :</p>

<ul>
<li><code>inherit</code> must be done first before <code>member</code> declarations</li>
<li>All member names must be different, taking into account inherited names</li>
</ul>

<h3 id="member-function-member"><code>member</code></h3>
```c++
template <class U, U T::*ptr_to_member>   Class &  member (const char * name_0);
```

<p>Declare a member of the class. The name must be in the <code>ascii-7</code> character set, with exception of spaces, control characters as well as <code>del</code> character.</p>

<blockquote><h6>W A R N I N G</h6> flip Member declaration must follow the same order as in the C++ class declaration.</blockquote>

<p>All member names must be different.</p>

<p>This function returns a reference to the <code>Class</code> to allow call chaining.</p>

<p>Example :</p>

```c++
class Model : public DataModel <Model> {};

class Root : public Object
{
public:
   Int   value;
   Float value2;
};

Model::declare <Root> ()
   .name ("myapp.Root")
   .member <Int, &Root::value> ("value")
   .member <Float, &Root::value2> ("value2");
```

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

<p>Example : \codeblock [language=c++] *** void  introspect (Root & root) {    for (const auto & member : root.get_class ().members ())    {       auto & obj = member._representative.from (root);       const char * name_0 = member._name_0;</p>

<p>// on the first loop iteration,       // 'obj' represents a reference to 'root.value'       // 'name_0' is "value"</p>

<p>// on the second loop iteration,       // 'obj' represents a reference to 'root.value2'       // 'name_0' is "value2"    } } ***</p>

<p><sup><a href="Bool.md">previous</a> | <a href="Collection.md">next</a></sup></p>

