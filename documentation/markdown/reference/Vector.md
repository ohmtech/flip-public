<p><sup><a href="Variant.md">previous</a></sup></p>

<h1>Vector Class Reference</h1>

<table><tr><td>Inherits from</td><td><code>Blob</code></td></tr>
<tr><td>Declared in</td><td><code>flip/Vector.h</code></td></tr>
</table>

```c++
template <class T> class Vector;
```

<p><code>flip::Vector</code> is an container of non flip Objects that are continguous in memory.</p>

<p>It is used to store a massive number of objects in a performant way, but is not inherently concurrent like <code>Array</code> or <code>Collection</code>, because the whole content of the vector is resent every time there is a change to it, instead of just changing one element.</p>

<p>This means that if two users are changing a property of an element in the vector, and if this operation is done concurrently, only one of the user will see his change applied, and the other user will have it rollbacked.</p>

<p>The more there is latency on the network, the more this concurrency problem shows. On the local aera network however, this problem would most likely rarely shows.</p>

<p>The <code>Vector</code> itself provides support for modification introspection. When modifying the content of the <code>Vector</code>, the previous representation of the vector is still present. However individual elements are not tracked.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>T</code></td><td>The type of the elements. <code>T</code> <em>shall not</em> inherit from <code>flip::Object</code></td></tr>
</table>

<h2>Member Types</h2>

<table><tr><td><code>value_type</code></td><td><code>T</code></td></tr>
<tr><td><code>reference</code></td><td><code>T &</code></td></tr>
<tr><td><code>const_reference</code></td><td><code>const T &</code></td></tr>
<tr><td><code>pointer</code></td><td><code>T *</code></td></tr>
<tr><td><code>const_pointer</code></td><td><code>const T *</code></td></tr>
<tr><td><code>const_iterator</code></td><td>Constant random access iterator</td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Vector</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Vector</code></td></tr>
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
</table>

<h3>Modifiers</h3>

<table><tr><td><code><a href="#member-function-clear">clear</a></code></td><td>Clears the contents</td></tr>
<tr><td><code><a href="#member-function-replace">replace</a></code></td><td>Replace a specified portion of the container</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Vector ();                                (1)
Vector (const Vector & other);            (2)
Vector (Vector && other);                 (3)
Vector (const std::vector <T> & value);   (4)
```

<ol>
<li>Default constructor, constructs an empty container.</li>
<li>Copy constructor. Constructs the container with a copy of elements of <code>other</code>.</li>
<li>Move constructor. Constructs the container by moving the elements of <code>other</code>.</li>
<li>Constructor. Constructs the container with a copy of elements of <code>value</code>.</li>
</ol>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Vector ();
```

<p>Destructor.</p>

<h3 id="member-function-operator %3D"><code>operator =</code></h3>
```c++
Vector & operator = (const Vector & other); (1)
Vector & operator = (Vector && other); (2)
Vector & operator = (const std::vector <T> & other); (3)
Vector & operator = (std::vector <T> && other); (4)
```

<p>Copy assignment operator.</p>

<ol>
<li>Copy assignment operator.</li>
<li>Move assignment operator.</li>
<li>Assignment operator by copying the elements of <code>other</code>.</li>
<li>Assignment operator by moving the elements of <code>other</code>.</li>
</ol>

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
<p>Returns an iterator to the beginning.</p>

<h3 id="member-function-end cend"><code>end cend</code></h3>
<p>Returns an iterator to the end.</p>

<h3 id="member-function-clear"><code>clear</code></h3>
```c++
void  clear ();
```

<p>Removes all the elements from the container.</p>

<h3 id="member-function-replace"><code>replace</code></h3>
```c++
void  replace (const_iterator it, const_iterator it_end, const std::vector <T> & value); (1)
template <class InputIterator>
void  replace (const_iterator it, const_iterator it_end, InputIterator it2, InputIterator it_end2); (2)
```

<p>Replaces the part of the container indicated by [it, it_end) with new elements.</p>

<p><sup><a href="Variant.md">previous</a></sup></p>

