<p><sup><a href="organize.md">previous</a> | <a href="observe.md">next</a></sup></p>

<h1>Controlling the Model</h1>

<p>Now that we can declare a model and we know how to organize it, this chapter describes how to manipulate it.</p>

<p>This chapter will use the model declared in the chapter <a href="../guide/declare.md">Declaring the Model</a>.</p>

<h2 id="document">The Document</h2>

<p>To manipulate the model, one must have an instance of the model which is called a <em>document</em>.</p>

<p>A <code>Document</code> is therefore described by the model it uses, a unique user 64-bit identifier, a manufacturer/product identifier as well as a component identifier. The latters only allows to know who is the originator of a modification and allows for concurrent modification of a document.</p>

```c++
#include "flip/DataModel.h"
#include "flip/Document.h"

class Model : public flip::DataModel <Model> {};

...code skipped...

void  run ()
{
   declare ();                                                       (1)

   Document document (Model::use (), 123456789ULL, 'acme', 'gui ');  (2)
}
```

<ol>
<li>You must first declare your model before you use it</li>
<li>This line will create a <code>Document</code> which uses <code>Model</code>, <code>123456789ULL</code> user unique identifier, <code>'acme'</code> manufacturer/product for the <code>'gui '</code> component</li>
</ol>

<h2 id="how">How it Works</h2>

<p>When you change the document, Flip will know that it was modified. Transactions represent the difference between two document states. When the document is modified, Flip internally keeps the old and new state of the document.</p>

<p>When you have done the necessary changes that represent a logical modification of the document, you can then <code>commit</code> the document to apply those changes.</p>

<p>In that sense, a transaction (or modification of the document) is always made so that the new document is valid from the model point of view.</p>

<h2 id="property">Modifying a Property</h2>

<p>For this example, let's suppose that we want to change the tempo.</p>

```c++
#include "flip/DataModel.h"
#include "flip/Document.h"

class Model : public flip::DataModel <Model> {};

...code skipped...

void  run ()
{
   declare ();

   Document document (Model::use (), 123456789ULL, 'acme', 'gui ');

   Song & song = document.root <Song> ();                            (1)

   song.tempo = 120.0;                                               (2)

   document.commit ();                                               (3)
}
```

<ol>
<li>This extract the unique <code>Song</code>, the root of the document.</li>
<li>This sets the tempo of the song to 120 beats per minutes, now the document is marked as modified.</li>
<li>This will apply the change to the document.</li>
</ol>

<p>Commiting a document marks the boundary of the document change, which is computed into a transaction.</p>

<h2 id="array">Working with <code>Array</code>s</h2>

<p>For this example, let's suppose that we want to insert a new track into the song. We suppose here that the document is already set up.</p>

```c++
class Song : public flip::Object
{
public:
   static void    declare ();

   Track &        add_track ();

   flip::Float    tempo;
   flip::Array <Track>
                  tracks;
};

Track &  Song::add_track ()
{
   auto it = tracks.emplace (tracks.end ());    (1)

   return *it;                                  (2)
}
```

<ol>
<li>Emplace a new track constructed in-place before the <code>end ()</code> <code>iterator</code>. This is similar to push a new element at the back of the <code>Array</code></li>
<li>Dereference the returned <code>iterator</code></li>
</ol>

<blockquote><h6>Note</h6> One should note that in the above example, the modification is not commited to the document.</blockquote>

<h2 id="collection">Working with <code>Collection</code>s</h2>

<p>For this example, let's suppose that we want to insert a new clip into the track.</p>

```c++
class Clip : public flip::Object
{
public:
   static void    declare ();

                  Clip () = default;
                  Clip (double position, double duration);

   flip::Float    position;
   flip::Float    duration;
};

class Track : public flip::Object
{
public:
   static void    declare ();

   Clip &         add_clip (double position, double duration);

   flip::Collection <Clip>
                  clips;
};

Clip &   Track::add_clip (double position, double duration)
{
   auto it = clips.emplace (clips.end (), position, duration);    (1)

   return *it;
}
```

<ol>
<li>Emplace a new clip constructed in-place with the second constructor of <code>Clip</code></li>
<li>Dereference the returned <code>iterator</code></li>
</ol>

<blockquote><h6>Note</h6> One should note that in the above example, the modification is not commited to the document.</blockquote>

<h2 id="variant">Working with <code>Variant</code>s</h2>

<p>For this example, let's suppose that the clip has some content which can be either audio or midi content. Let also suppose that no content is not permitted.</p>

<p>To do that, you would typically use a <code>Variant</code>.</p>

```c++
class Content : public flip::Object
{
public:
   static void    declare ();
};

class ContentAudio : public Content
{
public:
   static void    declare ();

   flip::String   url;
};

class ContentMidi : public Content
{
public:
   static void    declare ();

   flip::Blob     midi_events;
};


class Clip : public flip::Object
{
public:
   static void    declare ();

                  Clip () = default;
                  Clip (double position, double duration);

   flip::Float    position;
   flip::Float    duration;
   Variant <Content>
                  content;
};

class Track : public flip::Object
{
public:
   static void    declare ();

   Clip &         add_clip_audio (double position, double duration);

   flip::Collection <Clip>
                  clips;
};

Clip &   Track::add_clip_audio (double position, double duration, std::string url)
{
   auto it = clips.emplace (clips.end (), position, duration);

   auto & clip = *it;

   clip.content.reset <ContentAudio> ().url = url;    (1)

   return clip;
}
```

<ol>
<li>Set the content of the clip to be an audio content with its url</li>
</ol>

<blockquote><h6>Note</h6> One should note that in the above example, failure to provide an initial value to the variant at commit time will trigger a flip validation failure.</blockquote>

<h2 id="optional">Working with <code>Optional</code>s</h2>

<p>For this example, let's suppose that the clip has some content which can be either audio or midi content. Let also suppose that no content is allowed this time.</p>

<p>To do that, you would typically use a <code>Optional</code>.</p>

```c++
class Content : public flip::Object
{
public:
   static void    declare ();
};

class ContentAudio : public Content
{
public:
   static void    declare ();

   flip::String   url;
};

class ContentMidi : public Content
{
public:
   static void    declare ();

   flip::Blob     midi_events;
};


class Clip : public flip::Object
{
public:
   static void    declare ();

                  Clip () = default;
                  Clip (double position, double duration);

   flip::Float    position;
   flip::Float    duration;
   Optional <Content>
                  content;
};

class Track : public flip::Object
{
public:
   static void    declare ();

   Clip &         add_clip_audio (double position, double duration);

   flip::Collection <Clip>
                  clips;
};

Clip &   Track::add_clip_audio (double position, double duration, std::string url)
{
   auto it = clips.emplace (clips.end (), position, duration);

   auto & clip = *it;

   clip.content.reset <ContentAudio> ().url = url;                      (1)

   return clip;
}

Clip &   Track::add_clip_no_content (double position, double duration)  (2)
{
   auto it = clips.emplace (clips.end (), position, duration);

   return *it;
}
```

<ol>
<li>Set the content of the clip to be an audio content with its url</li>
<li>Set the content of the clip to none</li>
</ol>

<p>Now that we know how to modify the model in different situations, the next part will be about observing those changes with an observer, and is covered in the next chapter <a href="../guide/observe.md">Observing the Model</a>.</p>

<p><sup><a href="organize.md">previous</a> | <a href="observe.md">next</a></sup></p>

