<p><sup><a href="Class.md">previous</a> | <a href="Collection.iterator.md">next</a></sup></p>

<h1>Collection Class Reference</h1>

<table><tr><td>Inherits from</td><td><code>BasicType</code></td></tr>
<tr><td>Declared in</td><td><code>flip/Collection.h</code></td></tr>
</table>

```c++
template <class T> class Collection;
```

<p><code>flip::Collection</code> is an unordered container.</p>

<p>Addition or removal of the elements in the collection or accross collections does not invalidate the iterators or references.</p>

<p>The <code>Collection</code> itself provides support for modification introspection. When modifying the content of the <code>Collection</code>, the previous representation of the collection is still present, and can be accessed for every elements using the methods <code>added</code>, <code>resident</code> or <code>removed</code>.</p>

<blockquote><h6>W A R N I N G</h6> Unlike the C++ standard library, when an element is erased from a container, and if iterating over the container before <code>commit</code>, the element is still present until the modification is commited, but the element is marked as removed.</blockquote>

<p>This container is used when the elements have an <em>implicit</em> order of if order is not important. If two elements of the container can be compared, this defines an implicit order.</p>

<p>When elements order is needed but cannot be defined implicitly, then <a href="../reference/Array.md"><code>Array</code></a> shall be prefered.</p>

<p>Finally when a container needs to have an important number of elements and should be accessed with maximum speed, <a href="../reference/Vector.md"><code>Vector</code></a> could be prefered, acknowledging that the latter does not provide very good concurrency and its element are not flip objects.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>T</code></td><td>The type of the elements. <code>T</code> must inherit from <code>flip::Object</code></td></tr>
</table>

<h2>Member Types</h2>

<table><tr><td><code>value_type</code></td><td><code>T</code></td></tr>
<tr><td><code>reference</code></td><td><code>T &</code></td></tr>
<tr><td><code>const_reference</code></td><td><code>const T &</code></td></tr>
<tr><td><code>pointer</code></td><td><code>T *</code></td></tr>
<tr><td><code>const_pointer</code></td><td><code>const T *</code></td></tr>
<tr><td><a href="../reference/Collection.iterator.md"><code>iterator</code></a></td><td>Bidirectional access iterator</td></tr>
<tr><td><a href="../reference/Collection.iterator.md"><code>const_iterator</code></a></td><td>Constant bidirectional access iterator</td></tr>
<tr><td><a href="../reference/Collection.iterator.md"><code>reverse_iterator</code></a></td><td>Bidirectional access iterator</td></tr>
<tr><td><a href="../reference/Collection.iterator.md"><code>const_reverse_iterator</code></a></td><td>Constant bidirectional access iterator</td></tr>
<tr><td><code>difference_type</code></td><td><code>std::ptrdiff_t</code></td></tr>
<tr><td><code>size_type</code></td><td><code>std::size_t</code></td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Collection</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Collection</code></td></tr>
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
<tr><td><code><a href="#member-function-gbegin gcbegin">gbegin gcbegin</a></code></td><td>Returns a generic <code>collection_iterator</code> to the beginning</td></tr>
<tr><td><code><a href="#member-function-gend gcend">gend gcend</a></code></td><td>Returns a generic <code>collection_iterator</code> to the end</td></tr>
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
Collection ();                     (1)
Collection (const Collection & other);  (2)
```

<ol>
<li>Default constructor, constructs an empty container.</li>
<li>Copy constructor. Constructs the container with copy of elements of <code>other</code>.</li>
</ol>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Collection ();
```

<p>Destructor.</p>

<h3 id="member-function-operator %3D"><code>operator =</code></h3>
```c++
Collection & operator = (const Collection & other); (1)
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

<p>Example :</p>

```c++
void  Observer::document_changed (Note & note)
{
   if (note.added ())
   {
      // A note was added to the document. Create the corresponding
      // view element

      note.entity ().emplace <NoteView> ();
   }

   [...]
}
```

<h3 id="member-function-removed"><code>removed</code></h3>
```c++
bool  removed () const;
```

<p>Returns <code>true</code> <em>iff</em> the object was just detached from the document tree.</p>

<p>Example :</p>

```c++
void  Observer::document_changed (Note & note)
{
   [...]

   if (note.removed ())
   {
      // A note was removed from the document. Release the corresponding
      // view element

      note.entity ().erase <NoteView> ();
   }
}
```

<h3 id="member-function-resident"><code>resident</code></h3>
```c++
bool  resident () const;
```

<p>Returns <code>true</code> <em>iff</em> the object was neither attached nor detached from the document tree.</p>

<p>An object can be <code>resident</code> but moved. In this case the <code>iterator</code> pointing to it will allow to detect the move.</p>

<p>Example :</p>

```c++
void  Observer::document_changed (Array <Track> & tracks)
{
   auto it = tracks.begin ();
   auto it_end = tracks.end ();

   for (; it != it_end ; ++it)
   {
      Track & track = *it;

      if (it.added () && track.resident ())
      {
         // the track was moved in the container
         // this is the destination position
      }

      if (it.added () && track.resident ())
      {
         // the track was moved in the container
         // this is the source position
      }
   }
}
```

<h3 id="member-function-changed"><code>changed</code></h3>
```c++
bool  changed () const;
```

<p>Returns <code>true</code> <em>iff</em> the object or one of its children was modified.</p>

<p>Example :</p>

```c++
void  Observer::document_changed (Note & note)
{
   auto & view = note.entity ().use <ViewNote> ();

   if (note.changed ())
   {
      // one or more properties of the note changed

      if (note.position.changed ())
      {
         view.set_position (note.position);
      }

      if (note.duration.changed ())
      {
         view.set_duration (note.duration);
      }
   }
}
```

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

<p>Example :</p>

```c++
void  add_user (Root & root)
{
   // emplace a new User of the document to store
   // user specific data. User is constructed with
   // the unique user id number given at document
   // creation

   User & user = root.users.emplace <User> (root.document ().user ());

   // we don't want the scroll position in the document
   // to be part of undo
   user.scroll_position.disable_in_undo ();
}
```

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

<p>Example :</p>

```c++
// initially, note.position == 1

note.position = 2;
note.revert ();

// now, note.position == 1
```

<h3 id="member-function-begin cbegin"><code>begin cbegin</code></h3>
```c++
iterator       begin ();
const_iterator begin () const;
const_iterator cbegin () const;
```

<p>Returns an iterator to the beginning.</p>

<p>See <a href="../reference/Collection.iterator.md"><code>Collection::iterator</code></a> for more details.</p>

<h3 id="member-function-end cend"><code>end cend</code></h3>
```c++
iterator       end ();
const_iterator end () const;
const_iterator cend () const;
```

<p>Returns an iterator to the end.</p>

<p>See <a href="../reference/Collection.iterator.md"><code>Collection::iterator</code></a> for more details.</p>

<h3 id="member-function-rbegin crbegin"><code>rbegin crbegin</code></h3>
```c++
reverse_iterator       rbegin ();
const_reverse_iterator rbegin () const;
const_reverse_iterator crbegin () const;
```

<p>Returns a reverse iterator to the beginning.</p>

<p>See <a href="../reference/Collection.iterator.md"><code>Collection::iterator</code></a> for more details.</p>

<h3 id="member-function-rend crend"><code>rend crend</code></h3>
```c++
reverse_iterator       rend ();
const_reverse_iterator rend () const;
const_reverse_iterator crend () const;
```

<p>Returns a reverse iterator to the end.</p>

<p>See <a href="../reference/Collection.iterator.md"><code>Collection::iterator</code></a> for more details.</p>

<h3 id="member-function-gbegin gcbegin"><code>gbegin gcbegin</code></h3>
```c++
collection_iterator       gbegin ();
const_collection_iterator gbegin () const;
const_collection_iterator gcbegin () const;
```

<p>Returns a generic <code>collection_iterator</code> to the beginning.</p>

<p>Generic iterators are used to iterate over any template class <code>Collection</code> instance, whatever the specialization of the template class.</p>

<p>See <a href="../reference/collection_iterator.md"><code>collection_iterator</code></a> for more details.</p>

<h3 id="member-function-gend gcend"><code>gend gcend</code></h3>
```c++
collection_iterator       gbegin ();
const_collection_iterator gbegin () const;
const_collection_iterator gcbegin () const;
```

<p>Returns a generic <code>collection_iterator</code> to the end.</p>

<p>Generic iterators are used to iterate over any template class <code>Collection</code> instance, whatever the specialization of the template class.</p>

<p>See <a href="../reference/collection_iterator.md"><code>collection_iterator</code></a> for more details.</p>

<h3 id="member-function-clear"><code>clear</code></h3>
```c++
void  clear ();
```

<p>Removes all the elements from the container.</p>

<p>This is equivalent to calling <code>erase</code> on every non-removed element of the container.</p>

<h3 id="member-function-insert"><code>insert</code></h3>
```c++
iterator insert (const value_type & value);            (1)

template <class U>
iterator insert (const U & value);                     (2)

template <class U>
iterator insert (std::unique_ptr <U> && value);        (3)

template <class InputIterator>
void insert (InputIterator it, InputIterator it_end);  (4)
```

<ol>
<li>Inserts a copy of <code>value</code> in the container.</li>
<li>Inserts a copy of <code>value</code> of type <code>U</code> in the container.</li>
<li>Inserts by moving the content of <code>value</code> in the container.</li>
<li>Inserts a copy of the elements from range <code>[it, it_end)</code>.</li>
</ol>

<h3 id="member-function-emplace"><code>emplace</code></h3>
```c++
template <class... Args>
iterator emplace (Args &&... args);     (1)

template <class U, class... Args>
iterator emplace (Args &&... args);     (2)

iterator emplace (const Mold & mold);   (3)

template <class U>
iterator emplace (const Mold & mold);   (4)
```

<ol>
<li>Emplaces a new element constructed in-place with arguments <code>args</code>.</li>
<li>Emplaces a new element of type <code>U</code> constructed in-place with arguments <code>args</code>.</li>
<li>Emplaces a new element casted from <code>mold</code>.</li>
<li>Emplaces a new element of type <code>U</code> casted from <code>mold</code>.</li>
</ol>

<h3 id="member-function-erase"><code>erase</code></h3>
```c++
iterator erase (iterator it);
```

<p>Erases element at position <code>it</code>. Returns the <code>iterator</code> following <code>it</code>.</p>

<h3 id="member-function-splice"><code>splice</code></h3>
```c++
iterator splice (Collection & other, iterator it);
```

<p>Moves element at position <code>it</code> from <code>other</code> to <code>*this</code>. Returns an <code>iterator</code> to that element.</p>

<blockquote><h6>Note</h6> <code>other</code> and <code>*this</code> might <em>not</em> refer to the same object.</blockquote>

<p>To detect move in a container, see <a href="../reference/Collection.iterator.md"><code>Collection::iterator</code></a> for mode details.</p>

<p><sup><a href="Class.md">previous</a> | <a href="Collection.iterator.md">next</a></sup></p>

