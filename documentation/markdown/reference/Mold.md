<p><sup><a href="Message.md">previous</a> | <a href="MulticastServiceExplorer.md">next</a></sup></p>

<h1>Mold Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Mold.h</code></td></tr>
</table>

```c++
class Mold;
```

<p><code>flip::Mold</code> is a convencience type to make copies of flip objects. It is typically used in implementations of user interface copy/paste feature or making clones of an object.</p>

<p>The <code>Mold</code> itself is used in two ways :</p>

<ul>
<li>Making the mold by making an imprint of flip objects and get opaque data out of it</li>
<li>Casting the mold by giving the previous opaque data and produce flip objects</li>
</ul>

<p>The casting part is typically done using the <code>emplace</code> overload for mold in the flip containers.</p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Construct the <code>Mold</code></td></tr>
<tr><td><code><a href="#member-function-make">make</a></code></td><td>Add an object to the current mold</td></tr>
<tr><td><code><a href="#member-function-cure">cure</a></code></td><td>Cure the mold</td></tr>
<tr><td><code><a href="#member-function-cast">cast</a></code></td><td>Casts the mold</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Mold (const DataModelBase & model);                        (1)
Mold (const DataModelBase & model, StreamBinOut & sbo);    (2)
Mold (const DataModelBase & model, StreamBinIn & sbi);     (3)
Mold (Mold && other);                                      (4)
```

<ol>
<li>Constructs the <code>Mold</code> for making and casting without serialization</li>
<li>Constructs the <code>Mold</code> for making, by attaching it to a binary stream for writing</li>
<li>Constructs the <code>Mold</code> for casting, by attaching it to a binary stream for reading</li>
<li>Constructs the <code>Mold</code> by moving from <code>other</code> Mold</li>
</ol>

<p>For all constructors, the data model from which the mold is made or casted must be passed, to allow automatic flip object (not attached to a document) to be made or casted.</p>

<h3 id="member-function-make"><code>make</code></h3>
```c++
template <class T>   void  make (const T & obj, bool skip_container_flag = false);
```

<p>Add a flip object <code>obj</code> of type <code>T</code> to the current mold. If <code>skip_container_flag</code> is <code>true</code>, the mold will not contain the content of any flip container in the object sub-model tree.</p>

<blockquote><h6>Important</h6> This function can only be used in version (1) or (2) of the constructor.</blockquote>

<p>Example :</p>

```c++
class Note : public Object
{
public:
   Float position;
   Float duration;
};

class Clip : public Object
{
public:
   Float position;
   Collection <Note> notes;
};

class Track : public Object
{
public:
   String name;
   Array <Clip> clips;
};

std::vector <uint8_t> data;
StreamBinOut sbo (data);

// we can use the StreamBinOut not only for molds
// here, remember track unique reference identifier
sbo << track.ref ();

Mold mold (Model::use (), sbo);
mold.make (clip); // copies clip position and all notes properties
mold.make (clip.ancestor <Track> (), true);  // only track.name

mold.cure ();
// now 'data' is filled with a serialisation of the molded objects
```

<h3 id="member-function-cure"><code>cure</code></h3>
```c++
void  cure ();
```

<p>Cure the mold. This flushes all necessary data to the binary stream so that the mold is ready for casting.</p>

<blockquote><h6>Important</h6> This function can only be used in the version (2) of the constructor.</blockquote>

<h3 id="member-function-cast"><code>cast</code></h3>
```c++
template <class T>   T  cast () const;             (1)
template <class T>   void  cast (T & obj) const;   (2)
```

<ol>
<li>Cast the mold which element matches type <code>T</code> and return it</li>
<li>Cast the mold which element matches type <code>T</code> in the passed object parameter</li>
</ol>

<blockquote><h6>Important</h6> Those functions can only be used in the version (1) or (3) of the constructor.</blockquote>

<p>Example :</p>

```c++
std::vector <uint8_t> data = ...;   // from previous serialisation
StreamBinIn sbi (data);

// we can multiple molds in a StreamBinIn so run until we reach
// the end of stream
while (!sbi.is_eos ())
{
   // we used the StreamBinOut not only for mold (see above)
   Ref track_ref;
   sbi >> track_ref;

   Mold mold (Model::use (), sbi);
   // sbi stream is advanced by the mold size, and filled with deserialized data

   // make a clip copy and put it in to the track clips
   track.clips.emplace (mold);
}
```

<p><sup><a href="Message.md">previous</a> | <a href="MulticastServiceExplorer.md">next</a></sup></p>

