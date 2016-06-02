<p><sup><a href="array_iterator.md">previous</a> | <a href="BackEndIR.md">next</a></sup></p>

<h1>BackEndBinary Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/BackEndBinary.h</code></td></tr>
</table>

```c++
class BackEndBinary;
```

<p><code>flip::BackEndBinary</code> represents a concrete format data type which, using a <code>DataProvider</code> or <code>DataConsumer</code>, allows to read or write and fill a generic back end representation of a document.</p>

<p>The object itself does not hold any data, and just act as a parser/formatter from the intermediate representation of the document to the provider/consumer.</p>

<p><code>BackEndBinary</code> will format the data in binary :</p>

<ul>
<li>This format is compact</li>
<li>This format is robust and secure</li>
<li>This format is performant</li>
<li>This format is <em>not</em> human readable or editable</li>
</ul>

<p>See <a href="../reference/BackEndMl.md">BackEndMl</a> for a less compact, less robust, less secure and less performant format, but which is human readable and editable in any plain text editing software.</p>

<p>Normally, this class is used through the use of <a href="../reference/BackEndIR.md">BackEndIR</a> directly. See the documentation for more details.</p>

<p><code>DataProvider</code>s and <code>DataConsumer</code>s provides an abstraction to the underlying storage media from which to read or write to.</p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>BackEndBinary</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>BackEndBinary</code></td></tr>
<tr><td><code><a href="#member-function-write">write</a></code></td><td>Format the data from the intermediate representation to the data consumer</td></tr>
<tr><td><code><a href="#member-function-read">read</a></code></td><td>Parse the data from the data provider to the intermediate representation</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
BackEndBinary ();
```

<p>Default constructor.</p>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~BackEndBinary ();
```

<p>Destructor.</p>

<h3 id="member-function-write"><code>write</code></h3>
```c++
void  write (DataConsumerBase & consumer, const BackEndIR & ir);
```

<p>Format the data from the intermediate representation of the document and feed them to the consumer.</p>

<p>Example :</p>

```c++
#include "flip/BackEndBinary.h"
#include "flip/BackEndIR.h"
#include "flip/DataConsumerMemory.h"


Document document (Model::use (), user_id, manufacturer_id, component_id);

[...]

// put the result of document serialisation in 'data'
std::vector <uint8_t> data;
DataConsumerMemory consumer (data);

// get the backend intermediate representation
BackEndIR backend = document.write ();

// write the backend intermediate representation to binary, using the consumer
backend.write <BackEndBinary> (consumer);

// now 'data' is filled with the document serialisation in binary format
```

<h3 id="member-function-read"><code>read</code></h3>
```c++
void   read (DataProviderBase & provider, BackEndIR & ir);
```

<p>Parse the data from the data provider and fill the intermediate representation of the document.</p>

<p>Example :</p>

```c++
#include "flip/BackEndBinary.h"
#include "flip/BackEndIR.h"
#include "flip/DataProviderMemory.h"


// data is filled with a previous document serialisation from 'write' above
std::vector <uint8_t> data = ...;

DataProviderMemory provider (data);

// tell the backend to automatically recognize the binary format
BackEndIR backend;
backend.register_backend <BackEndBinary> ();

bool ok_flag = backend.read (provider);
if (!ok_flag) return;   // a corruption occured

Document document (Model::use (), user_id, manufacturer_id, component_id);

// change the document with the content of the backend
document.read (backend);

// commit the changes
document.commit ();
```

<p><sup><a href="array_iterator.md">previous</a> | <a href="BackEndIR.md">next</a></sup></p>

