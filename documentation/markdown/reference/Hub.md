<p><sup><a href="History.md">previous</a> | <a href="Int.md">next</a></sup></p>

<h1>Hub Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Hub.h</code></td></tr>
</table>

```c++
class Hub;
```

<p><code>Hub</code> allows to use different <code>Document</code>s on the same local machine, when for example documents are used in different threads or processes.</p>

<p>It allows them to communicate between them automatically, as well as allows to communicate with a remote server.</p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Hub</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Hub</code></td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
template <class... Ports>
Hub (const DataModelBase & data_model, uint64_t user_id, Ports &... ports);
```

<p>Constructs a <code>Hub</code>.</p>

<blockquote><h6>W A R N I N G</h6> The provided <code>data_model</code> and <code>user_id</code> must be the same as for all <code>Document</code>s connected to the <code>Hub</code>.</blockquote>

<p>The number of connected documents is not dynamic and is set statically as many <code>ports</code> when constructing the hub.</p>

<p>The following example shows a set up where one document is in the same thread and process as the hub, and the other document is living in a different process or thread.</p>

```c++
// port for the document in the same thread/process
PortDirect port;

// port for the other document in another thread/process
PortSocketTcp port2 (9090);

const auto user_id = 123456789ULL;

Hub hub (Model::use (), user_id, port, port2);

// make the local document
Document document (Model::use (), user_id, 'appl', 'gui ');
CarrierDirect carrier (document, port);

for (;;)
{
   // port2 needs to be processed regurarly for communication
   port2.process ();
}


[... in the other process ...]

// make remote document, notice that the document
// as a different component 'gui2'
Document document (Model::use (), user_id, 'appl', 'gui2');
CarrierSocketTcp carrier (document, 9090);

for (;;)
{
   // carrier needs to be processed regurarly for communication
   carrier.process ();
}
```

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Hub ();
```

<p>Destructor.</p>

<p><sup><a href="History.md">previous</a> | <a href="Int.md">next</a></sup></p>

