<p><sup><a href="Array.iterator.md">previous</a> | <a href="BackEndBinary.md">next</a></sup></p>

<h1>array_iterator Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/iterator.h</code></td></tr>
</table>

```c++
using array_iterator = ...;
using const_array_iterator = ...;
```

<p><code>array_iterator</code> satisfies the <code>BidirectionalIterator</code> C++ concept. It is a generic iterator that can be used to iterate other any specialization of <code>Array</code>.</p>

<h2>Member Types</h2>

<table><tr><td><code>value_type</code></td><td><code>Object</code></td></tr>
<tr><td><code>reference</code></td><td><code>Object &</code></td></tr>
<tr><td><code>pointer</code></td><td><code>Object *</code></td></tr>
<tr><td><code>iterator_category</code></td><td><code>std::bidirectional_iterator_tag</code></td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<h3>Miscellaneous</h3>

<table><tr><td><code><a href="#member-function-key">key</a></code></td><td>Returns the key associated to the iterator.</td></tr>
<tr><td><code><a href="#member-function-added">added</a></code></td><td>Returns <code>true</code> <em>iff</em> the iterator was added to the container.</td></tr>
<tr><td><code><a href="#member-function-removed">removed</a></code></td><td>Returns <code>true</code> <em>iff</em> the iterator was removed to the container.</td></tr>
<tr><td><code><a href="#member-function-resident">resident</a></code></td><td>Returns <code>true</code> <em>iff</em> the iterator was neither added or removed.</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-key"><code>key</code></h3>
```c++
const KeyFloat & key () const;
```

<p>Returns the key associated to the iterator.</p>

<h3 id="member-function-added"><code>added</code></h3>
```c++
bool added () const;
```

<p>Returns <code>true</code> <em>iff</em> the iterator was added to the container.</p>

<blockquote><h6>Note</h6> When an object is moved in the container, then the destination iterator is considered as added while the object is considered as resident.</blockquote>

<h3 id="member-function-removed"><code>removed</code></h3>
```c++
bool removed () const;
```

<p>Returns <code>true</code> <em>iff</em> the iterator was removed to the container.</p>

<blockquote><h6>Note</h6> When an object is moved in the container, then the source iterator is considered as removed while the object is considered as resident.</blockquote>

<h3 id="member-function-resident"><code>resident</code></h3>
```c++
bool resident () const;
```

<p>Returns <code>true</code> <em>iff</em> the iterator was neither added or removed.</p>

<p><sup><a href="Array.iterator.md">previous</a> | <a href="BackEndBinary.md">next</a></sup></p>

