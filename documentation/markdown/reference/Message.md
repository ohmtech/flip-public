<p><sup><a href="Int.md">previous</a> | <a href="Mold.md">next</a></sup></p>

<h1>Message Class Reference</h1>

<table><tr><td>Inherits from</td><td><code>BasicType</code></td></tr>
<tr><td>Declared in</td><td><code>flip/Message.h</code></td></tr>
</table>

```c++
template <class... Args>   class Message;
```

<p><code>flip::Message</code> is a type that allows signalling of non-persistent data. In particular, <code>flip::Message</code> is type-safe and endian-safe.</p>

<p>It is different from <code>flip::Signal</code> in the sense that it is part of a transaction and is broadcasted to every client in a collaboration scheme. In particular, receiving a message is done in the observer.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>Args...</code></td><td>The types of the elements that the <code>Message</code> signals.    Each element must be compatible with <code>StreamBinIn</code> and <code>StreamBinOut</code>.</td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Message</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Message</code></td></tr>
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

<h3>Sending & Receiving</h3>

<table><tr><td><code><a href="#member-function-send">send</a></code></td><td>Sends a message</td></tr>
<tr><td><code><a href="#member-function-get">get</a></code></td><td>Get messages</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Message ();
```

<ol>
<li>Default constructor.</li>
</ol>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Message ();
```

<p>Destructor.</p>

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

<h3 id="member-function-send"><code>send</code></h3>
```c++
Message &   send (Args... args);
```

<p>Sends a message. Multiple messages may be sent before commiting the document.</p>

<p>Example :</p>

```c++
class Root : public Object
{
public:
   Message <int, float> message;
}

Model::version ("test.document");
Model::declare <Root> ()
   .name ("Root")
   .member <Message <int, float>, &Root::message> ("message");

Document document (Model::use (), observer, 123456789UL, 'appl', 'gui ');

Root & root = document.root <Root> ();

root.message.send (20, 2.f);
root.message.send (25, 3.f);

document.commit ();
// observer will receive two messages :
// - the first with '20' and '2.f' as values
// - the second with '25' and '3.f' as values
// see below on how to receive messages in the observer

```

<h3 id="member-function-get"><code>get</code></h3>
```c++
template <class F>   void get (F f) const;
```

<p>Get the message(s) currently contained in <code>Message</code>.</p>

<p><code>F</code> is usually used as a lambda function, which must follow the following prototype :</p>

```c++
void (bool, Args...)
```

<p>The first boolean parameter is true if the current execution direction is forward, false otherwise.</p>

<p>Example :</p>

```c++
void  Observer::document_changed (Root & root)
{
   root.message.get ([](bool forward_flag, int val1, float val2){
      // in the example above, this lambda function will be called twice :
      // one with (forward_flag, val1, val2) == (true, 20, 2.f)
      // one with (forward_flag, val1, val2) == (true, 25, 3.f)
   });
}
```

<p><sup><a href="Int.md">previous</a> | <a href="Mold.md">next</a></sup></p>

