<p><sup><a href="about.md">previous</a> | <a href="organize.md">next</a></sup></p>

<h1>Declaring the Model</h1>

<p>When building a Flip compatible application, the first task is defining your model. The <code>Model</code> is a set of declarations that will be used together in a concrete <code>Document</code>. In this sense, the Model can be seen as a blueprint or template of the actual Documents you will make with.</p>

<p>To help you understand the Flip principles, this guide considers the following application :</p>

<ul>
<li>Your company is called <code>acme</code> and is making the application <code>product</code></li>
<li>The application is a simple audio application</li>
<li>The application manipulates songs</li>
<li>A song has a global tempo value, representing the number of beats per minutes</li>
<li>A song has an ordered list of tracks</li>
<li>Each track has a set of clips, which are implicitely ordered through their position</li>
<li>Each clip has a position and a duration, expressed in beats</li>
<li>They are two kind of clips : audio clips which contain an audio sample and "MIDI" clips which contain musical events</li>
</ul>

<h2 id="model">Declaring the Model</h2>

<p>Every class managed by flip needs to be part of a <em>model</em>. Therefore you first begin by declaring this model in your header files, and defines its revision string. The revision string represents a particular revision of the model itself, and is used when converting documents from one version to another.</p>

```c++
#include "flip/DataModel.h"

class Model : public flip::DataModel <Model> {};

void  declare ()
{
   Model::version ("1.0");
}
```

<h2 id="class">Declaring a Class</h2>

<p>Every class managed by flip will need to inherit from <code>flip::Object</code>, so the first thing is to inherit from it.</p>

<p>We will also need to declare the class before we can use it, so that we will add a <code>static</code> <code>declare</code> member.</p>

<p>Every model has exactly one root class. We could say that the root class, which represents the top level document class, is the song, and modelize this like the following example.</p>

```c++
#include "flip/Object.h"

class Song : public flip::Object
{
public:
   static void    declare ();
};

void  Song::declare ()
{
   Model::declare <Song> ().name ("acme.product.Song");
}
```

<p>Finally the function <code>declare</code> in the section above would now look like :</p>

```c++
void  declare ()
{
   Model::version ("1.0");

   Song::declare ();
}
```

<h2 id="member1">Adding the first Flip Member</h2>

<p>In our example, the tempo is a global property of the song. To modelize that, we can simply make the tempo a floating point member of the song and write this like in the following example.</p>

```c++
#include "flip/Float.h"
#include "flip/Object.h"

class Song : public flip::Object
{
public:
   static void    declare ();

   flip::Float    tempo;
};

void  Song::declare ()
{
   Model::declare <Song> ()
      .name ("acme.product.Song")
      .member <flip::Float, &Song::tempo> ("tempo");     (1)
}
```

<ol>
<li>Add the typed <code>Float</code>, <code>tempo</code> <code>Song</code> member, and give it the name <code>"tempo"</code></li>
</ol>

<blockquote><h6>Important</h6> Names are used for document writing, and are also used in conversions. As such, carefull naming of members is important.</blockquote>

<h2 id="member2">Adding the Flip Containers</h2>

<p>Flip provides different kinds of containers.</p>

<ul>
<li>One is a strictly linearly ordered sequence container, called <code>Array</code> which is a template class. It is similar to the C++ standard library container <code>std::list</code> or <code>std::vector</code></li>
<li>Another one is an unordered container, called <code>Collection</code> which is a template class. It is similar to the C++ standard library container <code>std::set</code></li>
<li>Another is a one element polymorphic container, called <code>Variant</code> which is a template class. It is similar to the boost template class <code>boost::variant</code></li>
<li>Another is a zero or one element polymorphic container, called <code>Optional</code> which is a template class. It is similar to the boost template class <code>boost::optional</code></li>
</ul>

<p>In our example, the Tracks are explicitely specified as an ordered list so we will use an <code>Array</code> container.</p>

<p>The clips are implictely specified as implicitely ordered by their position. In this case, an <code>Array</code> or <code>Collection</code> could be used, but generally implicitely ordered elements are better modelized using a <code>Collection</code>.</p>

<p>We then will modelize the track using a <code>Track</code> class, and the clip using a <code>Clip</code> class. The song contains tracks, and a track contains clips. This can be modelized as in the following example.</p>

```c++
#include "flip/Array.h"
#include "flip/Collection.h"
#include "flip/Float.h"
#include "flip/Object.h"

class Clip : public flip::Object
{
public:
   static void    declare ();

   flip::Float    position;
   flip::Float    duration;
};

class Track : public flip::Object
{
public:
   static void    declare ();

   flip::Collection <Clip>
                  clips;
};

class Song : public flip::Object
{
public:
   static void    declare ();

   flip::Float    tempo;
   flip::Array <Track>
                  tracks;
};

void  Clip::declare ()
{
   Model::declare <Clip> ()
      .name ("acme.product.Clip")
      .member <flip::Float, &Clip::position> ("position")
      .member <flip::Float, &Clip::duration> ("duration");
}

void  Track::declare ()
{
   Model::declare <Track> ()
      .name ("acme.product.Track")
      .member <flip::Collection <Clip>, &Track::clips> ("clips");
}

void  Song::declare ()
{
   Model::declare <Song> ()
      .name ("acme.product.Song")
      .member <flip::Float, &Song::tempo> ("tempo")
      .member <flip::Array <Track>, &Song::tracks> ("tracks");
}
```

<p>Finally the whole model declaration, the function <code>declare</code> in the section above, would now look like :</p>

```c++
void  declare ()
{
   Model::version ("1.0");

   Clip::declare ();
   Track::declare ();
   Song::declare ();
}
```

<h2 id="inheritance">Inheritance</h2>

<p>Flip provides inheritance features. It allows you to declare a Flip class as inherited from another Flip class. Inheritance provides parent class members importing as well as C++ polymorphism.</p>

<p>In our example, the clip is specified as being one of two kind : either a clip containing audio or a clip containing musical events.</p>

<p>Both type of clips share the same main clip properties position and duration. In the case of the example, we can introduce <code>ClipAudio</code> and <code>ClipMidi</code> which allows to support those two behaviors.</p>

```c++
class ClipAudio : public Clip             (1)
{
public:
   static void    declare ();

   flip::String   sample_url;
};

void  ClipAudio::declare ()
{
   Model::declare <MySubClass> ()
      .name ("acme.product.MySubClass")
      .inherit <MyClass> ()               (2)
      .member <flip::String, &ClipAudio::sample_url> ("sample_url");
}
```

<p>Then declaring the flip class will look like the following example.</p>

```c++
void  declare ()
{
   Model::version ("1.0");

   Clip::declare ();
   ClipAudio::declare ();
   ClipMidi::declare ();

   ... code skipped ...
}
```

<blockquote><h6>Important</h6> Make sure that the base class is declared <em>before</em>.</blockquote>

<h2 id="types">Flip Types</h2>

<p>Every class managed by flip may contain an unlimited number of either Flip basic types or your own custom Flip classes.</p>

<p>Flip offers categories of basic types :</p>

<ul>
<li>Value types that hold a value</li>
<li>Container types</li>
<li>Reference type</li>
<li>Signaling type</li>
</ul>

<h3 id="types-value">Value Types</h3>

<ul>
<li><code>flip::Bool</code> holds a boolean value</li>
<li><code>flip::Int</code> holds a 64-bit integer value</li>
<li><code>flip::Float</code> holds a 64-bit floating point value</li>
<li><code>flip::Enum</code> holds an <code>enum</code> value</li>
<li><code>flip::Blob</code> holds a dynamic-sized opaque blob of data</li>
</ul>

<h3 id="types-container">Container Types</h3>

<ul>
<li><code>flip::Array</code> is a strictly linear ordered sequence container similar to <code>std::list</code> or <code>std::vector</code></li>
<li><code>flip::Collection</code> is an unordered container similar to <code>std::set</code></li>
<li><code>flip::Variant</code> is an one element container similar to <code>boost::variant</code></li>
</ul>

<h3 id="types-reference">Reference Type</h3>

<ul>
<li><code>flip::ObjectRef</code> holds a reference to another object in the model tree. It is similar to a pointer</li>
</ul>

<h3 id="types-signal">Signaling Type</h3>

<ul>
<li><code>flip::Cue</code> allows to signal an object with arbitrary non-persistent data</li>
</ul>

<p>The next chapter, <a href="../guide/organize.md">Organizing your Code</a> will guide you through the task of organizing the model code.</p>

<p><sup><a href="about.md">previous</a> | <a href="organize.md">next</a></sup></p>

