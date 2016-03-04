<p><sup><a href="BackEndIR.md">previous</a> | <a href="Blob.md">next</a></sup></p>

<h1>BackEndMl Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/BackEndMl.h</code></td></tr>
</table>

```c++
class BackEndMl;
```

<p><code>flip::BackEndMl</code> represents a concrete format data type which, using a <code>DataProvider</code> or <code>DataConsumer</code>, allows to read or write and fill a generic back end representation of a document.</p>

<p>The object itself does not hold any data, and just act as a parser/formatter from the intermediate representation of the document to the provider/consumer.</p>

<p><code>BackEndMl</code> will format the data in a textual format with a specific markup language :</p>

<ul>
<li>This format is not compact</li>
<li>This format is not considered secure for production</li>
<li>This format is not performant</li>
<li>This format is human readable and editable in any plain text editing software</li>
</ul>

<p>See <a href="../reference/BackEndBinary.md">BackEndBinary</a> for a a format ready for production.</p>

<p>Normally, this class is used through the use of <a href="../reference/BackEndIR.md">BackEndIR</a> directly. See the documentation for more details.</p>

<p><code>DataProvider</code>s and <code>DataConsumer</code>s provides an abstraction to the underlying storage media from which to read or write to.</p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>BackEndMl</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>BackEndMl</code></td></tr>
<tr><td><code><a href="#member-function-write">write</a></code></td><td>Format the data from the intermediate representation to the data consumer</td></tr>
<tr><td><code><a href="#member-function-read">read</a></code></td><td>Parse the data from the data provider to the intermediate representation</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
BackEndMl ();
```

<p>Default constructor.</p>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~BackEndMl ();
```

<p>Destructor.</p>

<h3 id="member-function-write"><code>write</code></h3>
```c++
void  write (DataConsumerBase & consumer, const BackEndIR & ir);
```

<p>Format the data from the intermediate representation of the document and feed them to the consumer.</p>

<h3 id="member-function-read"><code>read</code></h3>
```c++
void   read (DataProviderBase & provider, BackEndIR & ir);
```

<p>Parse the data from the data provider and fill the intermediate representation of the document.</p>

<p><sup><a href="BackEndIR.md">previous</a> | <a href="Blob.md">next</a></sup></p>

