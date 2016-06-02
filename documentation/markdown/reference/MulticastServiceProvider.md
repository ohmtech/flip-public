<p><sup><a href="MulticastServiceExplorer.md">previous</a> | <a href="Object.md">next</a></sup></p>

<h1>MulticastServiceProvider Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/contrib/MulticastServiceProvider.h</code></td></tr>
</table>

```c++
class MulticastServiceProvider;
```

<blockquote><h6>Note</h6> Classes part of <code>contrib/</code> are not supported on every platform.</blockquote>

<p><code>MulticastServiceProvider</code> is used to automatically provide Flip services running on the Local Area Network. It uses UDP multicast to achieve it.</p>

<p>It is used in conjunction with <code>MulticastServiceExplorer</code>, see <a href="../reference/MulticastServiceExplorer.md"><code>flip::MulticastServiceExplorer</code></a></p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>MulticastServiceProvider</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>MulticastServiceProvider</code></td></tr>
<tr><td><code><a href="#member-function-process">process</a></code></td><td>Processes service providing</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
MulticastServiceProvider (uint16_t session_port, DocumentBase & document, std::map <std::string, std::string> metadata);                                                               (1)
MulticastServiceProvider (uint32_t multicast_ip, uint16_t port_min, uint16_t port_max, uint16_t session_port, DocumentBase & document, std::map <std::string, std::string> metadata);  (2)
```

<ol>
<li>Convenience default constructor (see below).</li>
<li>Constructor (see below).</li>
</ol>

<p>Version 2 of the constructor takes the multicast ip and a range of possible port to provide the service on. The range allows to find an available port in the case where ports are already used for multicast.</p>

<p>It also provides the <code>session_port</code> which is the port on which the Flip document server is listening for new connections.</p>

<p><code>DocumentBase</code> provides the model version to make sure that they are identical when connecting, and finally <code>metada</code> is arbitrary map of key values to provide more informational data to the service explorer.</p>

<p>Version 1 of the constructor uses default values as given by the class <code>MulticastService</code>.</p>

```c++
// Setup a server for session number 1234567890123
DocumentValidatorVoid validator;
DocumentServer document_server (Model::use (), validator, 1234567890123ULL);

// Setup a socket listening on TCP port 9090 to accept new connections.
PortTransportServerTcp port (document_server, 9090);

std::map <std::string, std::string> metadata;
metadata ["name"] = "My great session!";
metadata ["date"] = "2015/05/06";

MulticastServiceProvider provider (9090, document_server, metadata);

for (;;)
{
   // process incoming connections and transfers
   port.process ();

   // process provider
   provider.process ();
}
```

<h3 id="member-function-destructor">Destructor</h3>
```c++
~MulticastServiceProvider ();
```

<p>Destructor.</p>

<h3 id="member-function-process"><code>process</code></h3>
```c++
void  process ();
```

<p>Processes service providing. This function needs to be called regularly to let <code>MulticastServiceProvider</code> provide service. This function can be called often, as it only processes sockets when needed.</p>

<p><sup><a href="MulticastServiceExplorer.md">previous</a> | <a href="Object.md">next</a></sup></p>

