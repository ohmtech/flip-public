<p><sup><a href="Enum.md">previous</a> | <a href="Float.md">next</a></sup></p>

<h1>EnumClass Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/EnumClass.h</code></td></tr>
</table>

```c++
template <class T>   class EnumClass;
```

<p><code>flip::EnumClass</code> is a type that represents a declaration of a flip Enumeration. A concrete instance of this enumeration is acquired using an instance of the <a href="../reference/DataModel.md"><code>DataModel</code></a></p>

<h2>Member Functions Synopsys</h2>

<h3>Declaring</h3>

<table><tr><td><code><a href="#member-function-name">name</a></code></td><td>Set the name of the enumeration</td></tr>
<tr><td><code><a href="#member-function-member">member</a></code></td><td>Declare an enumerator of the enumeration</td></tr>
</table>

<h3>Accessing</h3>

<table><tr><td><code><a href="#member-function-name">name</a></code></td><td>Returns the name of the enumeration</td></tr>
<tr><td><code><a href="#member-function-enumerators">enumerators</a></code></td><td>Returns information on the enumerators of the enumeration</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-name"><code>name</code></h3>
```c++
EnumClass &  name (const char * name_0);
```

<p>Set the name of the enumeration. The name must be in the <code>ascii-7</code> character set, with exception of spaces, control characters as well as <code>del</code> character.</p>

<p>Names starting with <code>flip</code> are reserved.</p>

<p>This function returns a reference to the <code>EnumClass</code> to allow call chaining.</p>

<h3 id="member-function-member"><code>member</code></h3>
```c++
template <T val>   EnumClass &  enumerator (const char * name_0);
```

<p>Declare an enumerator of the enumeration. The name must be in the <code>ascii-7</code> character set, with exception of spaces, control characters as well as <code>del</code> character.</p>

<blockquote><h6>W A R N I N G</h6> flip Enumeration declaration must follow the same order as in the C++ enumeration declaration. must start from 0, and must be continguous.</blockquote>

<p>This function returns a reference to the <code>EnumClass</code> to allow call chaining.</p>

<h3 id="member-function-name"><code>name</code></h3>
```c++
const char *   name () const
```

<p>Returns the name of the enumeration.</p>

<h3 id="member-function-enumerators"><code>enumerators</code></h3>
```c++
const Enumerators &   enumerators () const
```

<p>Returns information on the enumerators of the enumeration. This allows for automatic introspection of an instance of the enumeration.</p>

<p><sup><a href="Enum.md">previous</a> | <a href="Float.md">next</a></sup></p>

