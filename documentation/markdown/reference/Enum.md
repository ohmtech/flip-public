<p><sup><a href="Entity.md">previous</a> | <a href="EnumClass.md">next</a></sup></p>

<h1>Enum Class Reference</h1>

<table><tr><td>Inherits from</td><td><code>BasicType</code></td></tr>
<tr><td>Declared in</td><td><code>flip/Enum.h</code></td></tr>
</table>

```c++
template <class T> class Enum;
```

<p><code>flip::Enum</code> is a type that represents an enumeration. The enumeration must start from the value 0.</p>

<p>Because every enumeration receive a textual name, it is has the main advantage, over a <code>flip::Int</code>, to make a markup language representation more easy to understand, as the textual name will be used instead of just a number.</p>

<p>See <a href="../reference/EnumClass.md"><code>EnumClass</code></a> to see how to declare an enumeration. In particular, the enumeration itself must be declared before an <code>Enum</code> member can be declared in the model.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>T</code></td><td>The enumeration type. <code>T</code> must be an <code>enum</code> or <code>enum class</code></td></tr>
</table>

<h2>Member Types</h2>

<table><tr><td><code>value_type</code></td><td><code>T</code></td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Enum</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Enum</code></td></tr>
<tr><td><code><a href="#member-function-operator %3D">operator =</a></code></td><td>Assigns value</td></tr>
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

<h3>Value Access</h3>

<table><tr><td><code><a href="#member-function-operator T">operator T</a></code></td><td>Returns the current value of the object</td></tr>
<tr><td><code><a href="#member-function-before">before</a></code></td><td>Returns the previous value of the object</td></tr>
</table>

<h3>Comparaison</h3>

<table><tr><td><code><a href="#member-function-operator %3D%3D">operator ==</a></code></td><td>Returns <code>true</code> <em>iff</em> objects current values are equal</td></tr>
<tr><td><code><a href="#member-function-operator %21%3D">operator !=</a></code></td><td>Returns <code>true</code> <em>iff</em> objects current values are different</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Enum ();                      (1)
Enum (const Enum & other);    (2)
Enum (T value);               (3)
```

<ol>
<li>Default constructor, constructs with a <code>0</code> value.</li>
<li>Copy constructor. Constructs the object with the value of <code>other</code>.</li>
<li>Constructor. Constructs the object with <code>value</code>.</li>
</ol>

<blockquote><h6>W A R N I N G</h6> Variant 3 of the constructor cannot be called from the default constructor of a flip object.</blockquote>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Enum ();
```

<p>Destructor.</p>

<h3 id="member-function-operator %3D"><code>operator =</code></h3>
```c++
Enum & operator = (const Enum & other);   (1)
Enum & operator = (T value);              (2)
```

<ol>
<li>Copy assignment operator.</li>
<li>Assignment operator. Assigns the object with <code>value</code>.</li>
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

<h3 id="member-function-operator T"><code>operator T</code></h3>
```c++
operator T () const;
```

<p>Returns the current value of the object.</p>

<h3 id="member-function-before"><code>before</code></h3>
```c++
T  before () const;
```

<p>Returns the previous value of the object.</p>

<h3 id="member-function-operator %3D%3D"><code>operator ==</code></h3>
```c++
bool  operator == (const Enum & rhs) const;
bool  operator == (T rhs) const;
```

<h3 id="member-function-operator %21%3D"><code>operator !=</code></h3>
```c++
bool  operator != (const Enum & rhs) const;
bool  operator != (T rhs) const;
```

<p><sup><a href="Entity.md">previous</a> | <a href="EnumClass.md">next</a></sup></p>

