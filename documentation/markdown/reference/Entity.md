<p><sup><a href="DocumentValidator.md">previous</a> | <a href="Enum.md">next</a></sup></p>

<h1>Entity Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Entity.h</code></td></tr>
</table>

```c++
class Entity;
```

<p><code>flip::Entity</code> is a generic associative container of any types where the key is the key type itself and the value an instance of that type.</p>

<p><code>Entity</code>s are used to store custom data in flip <code>Object</code>s and are typically used in observers.</p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><code><a href="#member-function-emplace">emplace</a></code></td><td>Constructs in-place a new element</td></tr>
<tr><td><code><a href="#member-function-erase">erase</a></code></td><td>Removes an element</td></tr>
<tr><td><code><a href="#member-function-use">use</a></code></td><td>Returns a reference to the element</td></tr>
<tr><td><code><a href="#member-function-get">get</a></code></td><td>Returns a pointer to the element</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-emplace"><code>emplace</code></h3>
```c++
template <class T, class... Args>   T &   emplace (Args &&... args);
```

<p>Constructs in-place a new element of type <code>T</code> by calling <code>T</code> constructor with variadic template parameters <code>args</code>.</p>

<blockquote><h6>W A R N I N G</h6> Only one instance of type <code>T</code> can exist in the entity.</blockquote>

<p>Returns a reference to the new in-place constructed element.</p>

<p>Example:</p>

```c++
class A
{
public:
   A (double value);
};

Entity entity;
entity.emplace <A> (2.5);
```

<h3 id="member-function-erase"><code>erase</code></h3>
```c++
template <class T>   void  erase ();
```

<p>Removes the element of type <code>T</code>.</p>

<blockquote><h6>W A R N I N G</h6> The element must exist in the entity.</blockquote>

<h3 id="member-function-use"><code>use</code></h3>
```c++
template <class T>   T &   use ();
```

<p>Returns a reference to the element of type <code>T</code>.</p>

<blockquote><h6>W A R N I N G</h6> The element must exist in the entity.</blockquote>

<h3 id="member-function-get"><code>get</code></h3>
```c++
template <class T>   T *   get ();
```

<p>Returns a pointer to the element of type <code>T</code> if it exists, <code>nullptr</code> otherwise.</p>

<p><sup><a href="DocumentValidator.md">previous</a> | <a href="Enum.md">next</a></sup></p>

