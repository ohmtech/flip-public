<p><sup><a href="Optional.md">previous</a> | <a href="Signal.md">next</a></sup></p>

<h1>Ref Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Ref.h</code></td></tr>
</table>

```c++
class Ref;
```

<p><code>flip::Ref</code> is a type that represents the unique reference number of a flip object.</p>

<p><center><img src="Ref.internal.png" /></center></p>

<p>It is essentialy 3 64-bit numbers.</p>

<ul>
<li>The <em>user</em> represents a unique user identifier (see below)</li>
<li>The <em>actor</em> represents a unique controller identifier (see below)</li>
<li>The <em>obj</em> represents a unique object identifier  for this user and actor (see below)</li>
</ul>

<p>When constructing a <code>Document</code> it is given a <code>user_id</code> as a parameter. This number shall be unique and represents a unique user number when using collaboration. Typically this can be an OpenId user identifier or a Facebook user number.</p>

<p>In the case where the user is working offline and never connected to your service and therefore doesn't have yet a unique identifier, the special identifier <code>Ref::User::Offline</code> may be used.</p>

<p>When constructing a <code>Document</code> it is given a <code>manufacturer_id</code> and a <code>component_id</code> which combines into a <code>actor_id</code>. This represents the actor as seen from the controller side and shall be unique. This is only relevant when using multiple <code>Document</code> with a <code>Hub</code> when documents are in separate threads or processes.</p>

<p>Finally, each time an object is created, a unique object identifier is created, so that the combinaison of those 3 64-numbers make a unique number in the whole document.</p>

<p>Since every <code>Ref</code> are unique in a document, one can extract an <code>Object</code> using a <code>Ref</code> and a <code>Document</code>. See <a href="../reference/Document.md"><code>Document</code></a> for more details.</p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Ref</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Ref</code></td></tr>
<tr><td><code><a href="#member-function-operator %3D">operator =</a></code></td><td>Assigns value</td></tr>
</table>

<h3>Decomposition</h3>

<table><tr><td><code><a href="#member-function-user">user</a></code></td><td>Returns the user unique id associated to this reference number</td></tr>
<tr><td><code><a href="#member-function-actor">actor</a></code></td><td>Returns the actor unique id associated to this reference number</td></tr>
<tr><td><code><a href="#member-function-obj">obj</a></code></td><td>Returns the object unique id associated to this reference number</td></tr>
</table>

<h3>Static Members</h3>

<h2>Member Variables Synopsys</h2>

<table><tr><td><code><a href="#member-variable-null">null</a></code></td><td>Represents the <code>null</code> reference number</td></tr>
<tr><td><code><a href="#member-variable-root">root</a></code></td><td>Represents the root object reference number of any document model</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Ref ();                    (1)
Ref (const Ref & other);   (2)
Ref (Ref && other);        (3)
```

<ol>
<li>Default constructor, constructs the <code>null</code> reference number.</li>
<li>Copy constructor. Constructs the object with the value of <code>other</code>.</li>
<li>Constructor. Constructs the object by moving <code>other</code>.</li>
</ol>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Ref ();
```

<p>Destructor.</p>

<h3 id="member-function-operator %3D"><code>operator =</code></h3>
```c++
Ref & operator = (const Ref & other);  (1)
Ref & operator = (Ref && other);  (1)
```

<ol>
<li>Copy assignment operator.</li>
<li>Assignment operator. Assigns the object by moving <code>other</code>.</li>
</ol>

<h3 id="member-function-user"><code>user</code></h3>
```c++
uint64_t user () const;
```

<p>Returns the user unique id associated to this reference number. User id from <code>0</code> to <code>3</code> are reserved.</p>

<h3 id="member-function-actor"><code>actor</code></h3>
```c++
uint64_t actor () const;
```

<p>Returns the actor unique id associated to this reference number.</p>

<h3 id="member-function-obj"><code>obj</code></h3>
```c++
uint64_t obj () const;
```

<p>Returns the object unique id associated to this reference number.</p>

<h2>Member Variables</h2>

<h3 id="member-variable-null"><code>null</code></h3>
```c++
static const Ref null;
```

<p>Represents the <code>null</code> reference number. Dereferencing this number will always returns <code>nullptr</code>.</p>

<h3 id="member-variable-root"><code>root</code></h3>
```c++
static const Ref root;
```

<p>Represents the root object reference number of any document model.</p>

<p><sup><a href="Optional.md">previous</a> | <a href="Signal.md">next</a></sup></p>

