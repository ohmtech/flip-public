<p><sup><a href="Array.iterator.md">next</a></sup></p>

<h1>Array Class Reference</h1>

<table><tr><td>Inherits from</td><td><code>BasicType</code></td></tr>
<tr><td>Declared in</td><td><code>flip/Array.h</code></td></tr>
</table>

```c++
template <class T> class Array;
```

<p><code>flip::Array</code> is a sequence container, that is its elements are ordered in a strict linear sequence.</p>

<p>Addition, removal and moving the elements within the array or accross arrays does not invalidate the iterators or references.</p>

<p>The <code>Array</code> itself provides support for modification introspection. When modifying the content of the <code>Array</code>, the previous representation of the array is still present.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>T</code></td><td>The type of the elements. <code>T</code> must inherit from <code>flip::Object</code></td></tr>
</table>

<h2>Member Types</h2>

<table><tr><td><code>value_type</code></td><td><code>T</code></td></tr>
<tr><td><code>reference</code></td><td><code>T &</code></td></tr>
<tr><td><code>const_reference</code></td><td><code>const T &</code></td></tr>
<tr><td><code>pointer</code></td><td><code>T *</code></td></tr>
<tr><td><code>const_pointer</code></td><td><code>const T *</code></td></tr>
<tr><td><a href="../reference/Array.iterator.md"><code>iterator</code></a></td><td>Bidirectional access iterator</td></tr>
<tr><td><a href="../reference/Array.iterator.md"><code>const_iterator</code></a></td><td>Constant bidirectional access iterator</td></tr>
<tr><td><a href="../reference/Array.iterator.md"><code>reverse_iterator</code></a></td><td>Bidirectional access iterator</td></tr>
<tr><td><a href="../reference/Array.iterator.md"><code>const_reverse_iterator</code></a></td><td>Constant bidirectional access iterator</td></tr>
<tr><td><code>difference_type</code></td><td><code>std::ptrdiff_t</code></td></tr>
<tr><td><code>size_type</code></td><td><code>std::size_t</code></td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Array</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Array</code></td></tr>
<tr><td><code><a href="#member-function-operator %3D">operator =</a></code></td><td>Assigns values to the container</td></tr>
</table>

<h3>Document Management</h3>

<table><tr><td><code><a href="#member-function-document">document</a></code></td><td>Returns the document to which the object is attached to</td></tr>
<tr><td><code><a href="#member-function-ref">ref</a></code></td><td>Returns the unique reference number of the object</td></tr>
<tr><td><code><a href="#member-function-added">added</a></code></td><td>Returns <code>true</code> <em>iff</em> the object was just attached to the document tree</td></tr>
<tr><td><code><a href="#member-function-removed">removed</a></code></td><td>Returns <code>true</code> <em>iff</em> the object was just detached from the document tree</td></tr>
<tr><td><code><a href="#member-function-resident">resident</a></code></td><td>Returns <code>true</code> <em>iff</em> the object was neither attached nor detached from the document tree</td></tr>
<tr><td><code><a href="#member-function-changed">changed</a></code></td><td>Returns <code>true</code> <em>iff</em> the object or one of its children was modified</td></tr>
<tr><td><code><a href="#member-function-ancestor">ancestor</a></code></td><td>Returns a reference to a parent in the current parent chain of the object</td></tr>
<tr><td><code><a href="#member-function-disable_in_undo">disable_in_undo</a></code></td><td>Disables the record state modification in history</td></tr>
<tr><td><code><a href="#member-function-inherit_in_undo">inherit_in_undo</a></code></td><td>Inherits the record state modification in history</td></tr>
<tr><td><code><a href="#member-function-is_in_undo_enabled">is_in_undo_enabled</a></code></td><td>Returns <code>true</code> <em>iff</em> this object modifications are recorded in history</td></tr>
<tr><td><code><a href="#member-function-revert">revert</a></code></td><td>Reverts all the changes make to the object and its children if any</td></tr>
</table>

<h3>Iterators</h3>

<table><tr><td><code><a href="#member-function-begin cbegin">begin cbegin</a></code></td><td>Returns an iterator to the beginning</td></tr>
<tr><td><code><a href="#member-function-end cend">end cend</a></code></td><td>Returns an iterator to the end</td></tr>
<tr><td><code><a href="#member-function-rbegin crbegin">rbegin crbegin</a></code></td><td>Returns a reverse iterator to the beginning</td></tr>
<tr><td><code><a href="#member-function-rend crend">rend crend</a></code></td><td>Returns a reverse iterator to the end</td></tr>
<tr><td><code><a href="#member-function-gbegin gcbegin">gbegin gcbegin</a></code></td><td>Returns a generic <code>array_iterator</code> to the beginning</td></tr>
<tr><td><code><a href="#member-function-gend gcend">gend gcend</a></code></td><td>Returns a generic <code>array_iterator</code> to the end</td></tr>
</table>

<h3>Modifiers</h3>

<table><tr><td><code><a href="#member-function-clear">clear</a></code></td><td>Clears the contents</td></tr>
<tr><td><code><a href="#member-function-insert">insert</a></code></td><td>Inserts elements</td></tr>
<tr><td><code><a href="#member-function-emplace">emplace</a></code></td><td>Constructs element in-place</td></tr>
<tr><td><code><a href="#member-function-erase">erase</a></code></td><td>Erases elements</td></tr>
<tr><td><code><a href="#member-function-splice">splice</a></code></td><td>Moves elements</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Array ();                     (1)
Array (const Array & other);  (2)
```

<ol>
<li>Default constructor, constructs an empty container.</li>
<li>Copy constructor. Constructs the container with copy of elements of <code>other</code>.</li>
</ol>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Array ();
```

<p>Destructor.</p>

<h3 id="member-function-operator %3D"><code>operator =</code></h3>
```c++
Array & operator = (const Array & other); (1)
```

<p>Copy assignment operator.</p>

<h3 id="member-function-document"><code>document</code></h3>
```c++
DocumentBase & document () const;
```

<p>Returns the document to which the object is attached to.</p>

<blockquote><h6>W A R N I N G</h6> Temporary flip objects are not attached to a document</blockquote>

<h3 id="member-function-ref"><code>ref</code></h3>
```c++
const Ref & ref () const;
```

<p>Returns the unique reference number of the object.</p>

<h3 id="member-function-added"><code>added</code></h3>
```c++
bool  added () const;
```

<p>Returns <code>true</code> <em>iff</em> the object was just attached to the document tree.</p>

<h3 id="member-function-removed"><code>removed</code></h3>
```c++
bool  removed () const;
```

<p>Returns <code>true</code> <em>iff</em> the object was just detached from the document tree.</p>

<h3 id="member-function-resident"><code>resident</code></h3>
```c++
bool  resident () const;
```

<p>Returns <code>true</code> <em>iff</em> the object was neither attached nor detached from the document tree.</p>

<h3 id="member-function-changed"><code>changed</code></h3>
```c++
bool  changed () const;
```

<p>Returns <code>true</code> <em>iff</em> the object or one of its children was modified.</p>

<h3 id="member-function-ancestor"><code>ancestor</code></h3>
```c++
template <class T>   T &   ancestor ();
template <class T>   const T &   ancestor () const;
```

<p>Returns a reference to a parent in the current parent chain of the object.</p>

<blockquote><h6>Note</h6> If an object or its parent is moved from one container to another, this function will always return the current parent, that is not the previous one</blockquote>

<h3 id="member-function-disable_in_undo"><code>disable_in_undo</code></h3>
```c++
void   disable_in_undo ();
```

<p>Disables the record state modification in history of the object and its subtree if any.</p>

<h3 id="member-function-inherit_in_undo"><code>inherit_in_undo</code></h3>
```c++
void   inherit_in_undo ();
```

<p>Inherits the record state modification in history of the object and its subtree if any, from its parent state. This is the default mode.</p>

<blockquote><h6>Note</h6> If the Root object of the tree is in inherited mode, then it is considered as enabled in undo.</blockquote>

<h3 id="member-function-is_in_undo_enabled"><code>is_in_undo_enabled</code></h3>
```c++
bool  is_in_undo_enabled () const;
```

<p>Returns <code>true</code> <em>iff</em> this object modifications are recorded in history. The function recursively search for disabled state starting from the object itself and navigating through the parent objects, if the state is inherited.</p>

<h3 id="member-function-revert"><code>revert</code></h3>
```c++
void  revert () const;
```

<p>Reverts all the changes make to the object and its children if any.</p>

<h3 id="member-function-begin cbegin"><code>begin cbegin</code></h3>
<h3 id="member-function-end cend"><code>end cend</code></h3>
<h3 id="member-function-rbegin crbegin"><code>rbegin crbegin</code></h3>
<h3 id="member-function-rend crend"><code>rend crend</code></h3>
<h3 id="member-function-gbegin gcbegin"><code>gbegin gcbegin</code></h3>
<h3 id="member-function-gend gcend"><code>gend gcend</code></h3>
<h3 id="member-function-clear"><code>clear</code></h3>
```c++
void  clear ();
```

<p>Removes all the elements from the container.</p>

<h3 id="member-function-insert"><code>insert</code></h3>
```c++
iterator insert (iterator pos, const value_type & value);            (1)

template <class U>
iterator insert (iterator pos, const U & value);                     (2)

template <class U>
iterator insert (iterator pos, std::unique_ptr <U> && value);        (3)

template <class InputIterator>
void insert (iterator pos, InputIterator it, InputIterator it_end);  (4)
```

<ol>
<li>Inserts a copy of <code>value</code> in the container before position <code>pos</code>.</li>
<li>Inserts a copy of <code>value</code> of type <code>U</code> in the container before position <code>pos</code>.</li>
<li>Inserts by moving the content of <code>value</code> in the container before position <code>pos</code>.</li>
<li>Inserts a copy of the elements from range <code>[it, it_end)</code> before position <code>pos</code>.</li>
</ol>

<h3 id="member-function-emplace"><code>emplace</code></h3>
```c++
template <class... Args>
iterator emplace (iterator pos, Args &&... args);     (1)

template <class U, class... Args>
iterator emplace (iterator pos, Args &&... args);     (2)

iterator emplace (iterator pos, const Mold & mold);   (3)

template <class U>
iterator emplace (iterator pos, const Mold & mold);   (4)
```

<ol>
<li>Emplaces a new element constructed in-place with arguments <code>args</code> before position <code>pos</code>.</li>
<li>Emplaces a new element of type <code>U</code> constructed in-place with arguments <code>args</code> before position <code>pos</code>.</li>
<li>Emplaces a new element casted from <code>mold</code> before position <code>pos</code>.</li>
<li>Emplaces a new element of type <code>U</code> casted from <code>mold</code> before position <code>pos</code>.</li>
</ol>

<h3 id="member-function-erase"><code>erase</code></h3>
```c++
iterator erase (iterator it);                (1)
void  erase (iterator it, iterator it_end);  (2)
```

<ol>
<li>Erases element at position <code>it</code>. Returns the <code>iterator</code> following <code>it</code>.</li>
<li>Erases elements in the range <code>[it, it_end)</code>.</li>
</ol>

<h3 id="member-function-splice"><code>splice</code></h3>
```c++
iterator splice (iterator pos, Array & other, iterator it);
```

<p>Moves element at position <code>it</code> from <code>other</code> to <code>*this</code> before position <code>pos</code>. Returns an <code>iterator</code> to that element.</p>

<blockquote><h6>Note</h6> <code>other</code> and <code>*this</code> might refer to the same object, allowing an object to move inside the container.</blockquote>

<p><sup><a href="Array.iterator.md">next</a></sup></p>

