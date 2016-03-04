<p><sup><a href="Mold.md">previous</a> | <a href="ObjectRef.md">next</a></sup></p>

<h1>Object Class Reference</h1>

<table><tr><td>Inherits from</td><td><code>Type</code></td></tr>
<tr><td>Declared in</td><td><code>flip/Object.h</code></td></tr>
</table>

```c++
class Object;
```

<p><code>flip::Object</code> is the base type to provide custom flip classes.</p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Object</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Object</code></td></tr>
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

<h3>Miscellaneous</h3>

<table><tr><td><code><a href="#member-function-parent">parent</a></code></td><td>Returns the current or previous parent of the object</td></tr>
<tr><td><code><a href="#member-function-entity">entity</a></code></td><td>Returns an entity</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Object ();                    (1)
Object (const Object & other);   (2)
```

<ol>
<li>Default constructor, constructs with a <code>0LL</code> value.</li>
<li>Copy constructor. Constructs the object with the value of <code>other</code>.</li>
</ol>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Object ();
```

<p>Destructor.</p>

<h3 id="member-function-operator %3D"><code>operator =</code></h3>
```c++
Object & operator = (const Object & other);
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

<h3 id="member-function-parent"><code>parent</code></h3>
```c++
template <class T>   T &   parent ();
Parent & parent ();
```

<p>Returns the current or previous parent of the object.</p>

<p>Example:</p>

```c++
object.parent <MyClass> ();                  (1)
object.parent ().ptr <MyClass> ();           (2)
object.parent ().before <MyClass> ();        (3)
object.parent ().before_ptr <MyClass> ();    (4)
```

<ol>
<li>Return the current parent as <code>MyClass</code>, throws if casting is incorrect</li>
<li>Return the current parent as <code>MyClass</code>, returns <code>nullptr</code> if casting is incorrect</li>
<li>Return the previous parent as <code>MyClass</code>, throws if casting is incorrect</li>
<li>Return the previous parent as <code>MyClass</code>, returns <code>nullptr</code> if casting is incorrect</li>
</ol>

<h3 id="member-function-entity"><code>entity</code></h3>
```c++
Entity & entity ();
```

<p>Returns an entity. <code>Entity</code> are described in details <a href="../reference/Entity.md">here</a>.</p>

<blockquote><h6>Note</h6> Entities can be made available in all types (including all basic types like <code>Int</code>    and <code>Array</code>) by defining the macro <code>flip_ENTITY_LOCATION</code>    to <code>flip_ENTITY_LOCATION_TYPE</code></blockquote>

<p><sup><a href="Mold.md">previous</a> | <a href="ObjectRef.md">next</a></sup></p>

