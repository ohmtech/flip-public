<p><sup><a href="about.md">previous</a> | <a href="language.md">next</a></sup></p>

<h1>Utml Overview</h1>

<p>This chapter gives a quick overview of Flip Utml (Unit Testing Markup Language) and practical examples.</p>

<h2 id="what">What is Utml ?</h2>

<p>Utml is a simple and compact markup language that can easily produce documents given an utml document and a data model. Since it is very compact, it can be used to generate unit testing easily.</p>

<blockquote><h6>Note</h6> Utml is not a backend format, it shall not be used in production.</blockquote>

<h2 id="example">Example of Utml</h2>

<p>Let's consider the following Flip data model declaration :</p>

```c++
class Note : public Object
{
public:
   Float position;
   Float duration;
};
using Notes = Collection <Note>;

class Track : public Object
{
public:
   String name;
   Notes  notes;
};
using Tracks = Array <Track>;

class Song : public Object
{
public:
   Bool   playing;
   Tracks tracks;
};
```

<p>Utml can be used to generate quickly a full song. The following exposes an example of a song with one track named "Bass" which contains two notes and is also in a playing state.</p>

```
Song {
   tracks = {
      Track {
         name = "Bass"
         notes = {
            Note { duration = 2 }
            Note { position = 1.5 duration = 2.3 }
         }
      }
   }
   playing = true
}
```

<p>In the previous example, because the <code>Note</code> <code>position</code> is not defined it is assumed to be 0.</p>

<p>Members can also be defined in whatever order, they don't need to follow the <code>C++</code> model declaration.</p>

<p>The client can then make a Flip document out of this utml source.</p>

```c++
#include "flip/contrib/Utml.h"

std::string utml_source = [utml source above];
std::vector <uint8_t> data (utml_source.begin (), utml_source.end ());
DataProviderMemory provider (data);

BackEndIR backend = Utml::read (provider, Model::use ());

document.read (backend);
```

<p><sup><a href="about.md">previous</a> | <a href="language.md">next</a></sup></p>

