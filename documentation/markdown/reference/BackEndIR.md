<p><sup><a href="BackEndBinary.md">previous</a> | <a href="BackEndMl.md">next</a></sup></p>

<h1>BackEndIR Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/BackEndIR.h</code></td></tr>
</table>

```c++
class BackEndIR;
```

<p><code>flip::BackEndIR</code> represents an intermediate representation of the document. Instead of directly to matching to flip class members, this objects holds class and attribute names as strings, allowing to modify this representation before it is fed to the document.</p>

<p>The object holds the full document in memory.</p>

<p>This class is used to :</p>

<ul>
<li>Read and write a document stored on a media</li>
<li>Convert from one revision of the document model to another one</li>
<li>Make the difference between two documents and make a transaction out of it,    which allows to produce 3-way merges</li>
</ul>

<h2>Member Types</h2>

<table><tr><td><code>Type</code></td><td>A generic flip Type representation</td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>BackEndIR</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>BackEndIR</code></td></tr>
<tr><td><code><a href="#member-function-clear">clear</a></code></td><td>Empty the representation</td></tr>
<tr><td><code><a href="#member-function-empty">empty</a></code></td><td>Returns <code>true</code> <em>iff</em> the representation is empty</td></tr>
</table>

<h3>BackEnd format to/from Intermediate Representation</h3>

<table><tr><td><code><a href="#member-function-register_backend">register_backend</a></code></td><td>Registers a concrete format backend for reading</td></tr>
<tr><td><code><a href="#member-function-read">read</a></code></td><td>Reads from the provider and fill this object. Returns <code>true</code> <em>iff</em> the operation was successful</td></tr>
<tr><td><code><a href="#member-function-write">write</a></code></td><td>Writes to the consumer using the specified backend in the template parameter</td></tr>
</table>

<h3>Intermediate Representation to/from Document</h3>

<table><tr><td><code><a href="#member-function-read">read</a></code></td><td>Reads from this object and fill the document</td></tr>
<tr><td><code><a href="#member-function-write">write</a></code></td><td>Writes to this object from the document</td></tr>
</table>

<h2>Member Variables Synopsys</h2>

<table><tr><td><code><a href="#member-variable-version">version</a></code></td><td>Version string as passed in the data model</td></tr>
<tr><td><code><a href="#member-variable-root">root</a></code></td><td>Variable representing the root of the whole document model tree</td></tr>
<tr><td><code><a href="#member-variable-member_names">member_names</a></code></td><td>Set of all member names in the document</td></tr>
<tr><td><code><a href="#member-variable-typenames">typenames</a></code></td><td>Set of all type names in the document</td></tr>
</table>

<h3>Type</h3>

<table><tr><td><code><a href="#member-variable-Type%3A%3Aref">Type::ref</a></code></td><td>Unique reference number of object</td></tr>
<tr><td><code><a href="#member-variable-Type%3A%3Atype_name">Type::type_name</a></code></td><td>Type name as declared in the data model</td></tr>
<tr><td><code><a href="#member-variable-Type%3A%3Amembers">Type::members</a></code></td><td>List of members of the object</td></tr>
<tr><td><code><a href="#member-variable-Type%3A%3Avalue">Type::value</a></code></td><td>Value of the object</td></tr>
<tr><td><code><a href="#member-variable-Type%3A%3Acollection">Type::collection</a></code></td><td>Elements of the collection</td></tr>
<tr><td><code><a href="#member-variable-Type%3A%3Aarray">Type::array</a></code></td><td>Elements of the array</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
BackEndIR ();                       (1)
BackEndIR (const BackEndIR & rhs);  (2)
BackEndIR (BackEndIR && rhs);       (3)
```

<ol>
<li>Default constructor. Constructs an empty representation</li>
<li>Copy constructor. Constructs as a copy of <code>rhs</code></li>
<li>Move constructor. Constructs by moving <code>rhs</code></li>
</ol>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~BackEndIR ();
```

<p>Destructor.</p>

<h3 id="member-function-clear"><code>clear</code></h3>
```c++
void  clear ();
```

<p>Empty the representation.</p>

<h3 id="member-function-empty"><code>empty</code></h3>
```c++
bool  empty () const;
```

<p>Returns <code>true</code> <em>iff</em> the representation is empty.</p>

<h3 id="member-function-register_backend"><code>register_backend</code></h3>
```c++
template <class BackEnd>
void  register_backend ();
```

<p>Register a concrete format backend such as <a href="../reference/BackEndBinary.md"><code>BackEndBinary</code></a> or <a href="../reference/BackEndMl.md"><code>BackEndMl</code></a>. Registering will allow this object to guess the format of the backend and do proper parsing.</p>

<p>The subsequent call to <code>read</code> will use all backends registered to this object.</p>

<p>Example:</p>

```c++
// DataProviderMemory provider;

BackEndIR backend;
backend.register_backend <BackEndBinary> (); (1)
backend.read (provider);                     (2)
```

<ol>
<li>Add <code>BackEndBinary</code> to the list of registered back end types to consider for reading</li>
<li>Read document given provider. In this case the backend will only use <code>BackEndBinary</code> for reading</li>
</ol>

<h3 id="member-function-read"><code>read</code></h3>
```c++
bool  read (DataProviderBase & provider);
```

<p>Reads from the provider and fill the intermediate representation of the document stored in this object.</p>

<p>Returns <code>true</code> <em>iff</em> the operation was successful.</p>

<p>See <a href="../reference/BackEndMl.md"><code>BackEndMl</code></a> or <a href="../reference/BackEndBinary.md"><code>BackEndBinary</code></a> for an example of use of this method.</p>

<h3 id="member-function-write"><code>write</code></h3>
```c++
template <class BackEnd>
void  write (DataConsumerBase & consumer);
```

<p>Writes the intermediate representation of the document to the consumer using the specified backend in the template parameter.</p>

<p>Example:</p>

```c++
// DataConsumerMemory consumer;

backend.write <BackEndBinary> (consumer);
```

<p>See <a href="../reference/BackEndMl.md"><code>BackEndMl</code></a> or <a href="../reference/BackEndBinary.md"><code>BackEndBinary</code></a> for a more detailed example of use of this method.</p>

<h3 id="member-function-read"><code>read</code></h3>
```c++
void  read (DocumentBase & document);
```

<p>Reads from this object and fill the document. It will modify the document exactly as if executing a transaction. Changed made to the document should then be commited.</p>

<p>See <a href="../reference/BackEndMl.md"><code>BackEndMl</code></a> or <a href="../reference/BackEndBinary.md"><code>BackEndBinary</code></a> for an example of use of this method.</p>

<h3 id="member-function-write"><code>write</code></h3>
```c++
void  write (DocumentBase & document);
```

<p>Writes to this object from the document.</p>

<h2>Member Variables</h2>

<h3 id="member-variable-version"><code>version</code></h3>
```c++
std::string version;
```

<p>This variable represents the version string as passed in the data model when declaring it.</p>

<h3 id="member-variable-root"><code>root</code></h3>
```c++
Type  root;
```

<p>This variable represents the root of the whole document model tree.</p>

<p>Typically, converting a document to one model revision to another consists of manipulating the data stored in that tree. The members of <code>Type</code> are exposed below.</p>

```c++
class Type
{
public:
   Ref                                          ref;
   std::string                                  type_name;
   std::list <std::pair <std::string, Type>>    members;
   Value                                        value;
   std::map <KeyRandom, Type>                   collection;
   std::map <KeyFloat, Type>                    array;
};
```

<p>The details of each variable members of type are exposed below.</p>

<h3 id="member-variable-member_names"><code>member_names</code></h3>
```c++
Names member_names;
```

<p>This variable represents the set of all member names in the document. It is used by some backend format to provide symbolic compression of names.</p>

<h3 id="member-variable-typenames"><code>typenames</code></h3>
```c++
Names typenames;
```

<p>This variable represents the set of all type names in the document. It is used by some backend format to provide symbolic compression of names.</p>

<h3 id="member-variable-Type%3A%3Aref"><code>Type::ref</code></h3>
```c++
Ref ref;
```

<p>This variable represents the unique reference number of the object.</p>

<blockquote><h6>W A R N I N G</h6> When converting a document and adding a member to a flip class, caution should be taken for the reference number not to collide.</blockquote>

<h3 id="member-variable-Type%3A%3Atype_name"><code>Type::type_name</code></h3>
```c++
std::string type_name;
```

<p>This variable represents the type name as declared in the data model.</p>

<h3 id="member-variable-Type%3A%3Amembers"><code>Type::members</code></h3>
```c++
std::list <std::pair <std::string, Type>> members;
```

<p><em>iff</em> the type represents a flip object, this variable represents the list of members of the object. The list itself is a <code>std::pair</code> which first element is the name of the member, and the second element a <code>Type</code>.</p>

<h3 id="member-variable-Type%3A%3Avalue"><code>Type::value</code></h3>
```c++
Value value;
```

<p><em>iff</em> the type represents a flip basic type and not a container, this variable represents the value of the object. The <code>Value</code> type holds value for all basic types.</p>

<h3 id="member-variable-Type%3A%3Acollection"><code>Type::collection</code></h3>
```c++
std::map <KeyRandom, Type> collection;
```

<p><em>iff</em> the type represents a collection, this variable represents the elements of the object.</p>

<blockquote><h6>Important</h6> For proper tracking of objects for document differentiation, the value of <code>KeyRandom</code> must not be changed.</blockquote>

<h3 id="member-variable-Type%3A%3Aarray"><code>Type::array</code></h3>
```c++
std::map <KeyFloat, Type>  array;
```

<p><em>iff</em> the type represents a array, this variable represents the elements of the object.</p>

<blockquote><h6>Important</h6> For proper tracking of objects for document differentiation, the value of <code>KeyFloat</code> must not be changed.</blockquote>

<p><sup><a href="BackEndBinary.md">previous</a> | <a href="BackEndMl.md">next</a></sup></p>

