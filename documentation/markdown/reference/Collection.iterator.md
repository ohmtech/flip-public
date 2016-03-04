<p><sup><a href="Collection.md">previous</a> | <a href="collection_iterator.md">next</a></sup></p>

<h1>Collection::iterator Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Collection.h</code></td></tr>
</table>

```c++
template <class T> class Collection
{
class iterator;
class const_iterator;
class reverse_iterator;
class const_reverse_iterator;
};
```

<p><code>Collection::iterator</code> satisfies the <code>BidirectionalIterator</code> C++ concept.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>T</code></td><td>The type of the elements. <code>T</code> must inherit from <code>flip::Object</code></td></tr>
</table>

<h2>Member Types</h2>

<table><tr><td><code>value_type</code></td><td><code>T</code></td></tr>
<tr><td><code>reference</code></td><td><code>T &</code></td></tr>
<tr><td><code>pointer</code></td><td><code>T *</code></td></tr>
<tr><td><code>difference_type</code></td><td><code>std::ptrdiff_t</code></td></tr>
<tr><td><code>iterator_category</code></td><td><code>std::bidirectional_iterator_tag</code></td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<h3>Miscellaneous</h3>

<table><tr><td><code><a href="#member-function-added">added</a></code></td><td>Returns <code>true</code> <em>iff</em> the iterator was added to the container.</td></tr>
<tr><td><code><a href="#member-function-removed">removed</a></code></td><td>Returns <code>true</code> <em>iff</em> the iterator was removed to the container.</td></tr>
<tr><td><code><a href="#member-function-resident">resident</a></code></td><td>Returns <code>true</code> <em>iff</em> the iterator was neither added or removed.</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-added"><code>added</code></h3>
```c++
bool added () const;
```

<p>Returns <code>true</code> <em>iff</em> the iterator was added to the container.</p>

<blockquote><h6>Note</h6> When an object is moved between containers, then the destination iterator is considered as added while the object is considered as resident.</blockquote>

<h3 id="member-function-removed"><code>removed</code></h3>
```c++
bool removed () const;
```

<p>Returns <code>true</code> <em>iff</em> the iterator was removed to the container.</p>

<blockquote><h6>Note</h6> When an object is moved between containers, then the source iterator is considered as removed while the object is considered as resident.</blockquote>

<h3 id="member-function-resident"><code>resident</code></h3>
```c++
bool resident () const;
```

<p>Returns <code>true</code> <em>iff</em> the iterator was neither added or removed.</p>

<p><sup><a href="Collection.md">previous</a> | <a href="collection_iterator.md">next</a></sup></p>

