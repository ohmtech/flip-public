<p><sup><a href="Mold.md">previous</a> | <a href="MulticastServiceProvider.md">next</a></sup></p>

<h1>MulticastServiceExplorer Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/contrib/MulticastServiceExplorer.h</code></td></tr>
</table>

```c++
class MulticastServiceExplorer;
```

<blockquote><h6>Note</h6> Classes part of <code>contrib/</code> are not supported on every platform.</blockquote>

<p><code>MulticastServiceExplorer</code> is used to automatically discover over Flip services running on the Local Area Network. It uses UDP multicast to achieve it.</p>

<p>It is used in conjunction with <code>MulticastServiceProvider</code>, see <a href="../reference/MulticastServiceProvider.md"><code>flip::MulticastServiceProvider</code></a></p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>MulticastServiceExplorer</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>MulticastServiceExplorer</code></td></tr>
<tr><td><code><a href="#member-function-set_update_period">set_update_period</a></code></td><td>Sets the refresh period</td></tr>
<tr><td><code><a href="#member-function-process">process</a></code></td><td>Processes exploration</td></tr>
<tr><td><code><a href="#member-function-begin">begin</a></code></td><td>Returns an iterator to the first session</td></tr>
<tr><td><code><a href="#member-function-end">end</a></code></td><td>Returns an iterator to the end</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
MulticastServiceExplorer ();                                                              (1)
MulticastServiceExplorer (uint32_t multicast_ip, uint16_t port_min, uint16_t port_max);   (2)
```

<ol>
<li>Convenience default constructor (see below).</li>
<li>Constructor (see below).</li>
</ol>

<p>Version 2 of the constructor takes the multicast ip and a range of port to explore on.</p>

<p>Version 1 of the constructor uses default values as given by the class <code>MulticastService</code>.</p>

```c++
MulticastServiceExplorer explorer;

bool loop_flag = true;

// busy wait until we have at least one session discovered
while (loop_flag)
{
   explorer.process ();

   loop_flag = explorer.begin () == explorer.end ();
}

// look up the available sessions
for (auto && session : explorer)
{
   session.ip;       // IP of Flip server on the network
   session.port;     // Port of Flip server
   session.version;  // Version of Flip server

   session.metadata; // Map of arbitrary metadatas associated to the session
}
```

<h3 id="member-function-destructor">Destructor</h3>
```c++
~MulticastServiceExplorer ();
```

<p>Destructor.</p>

<h3 id="member-function-set_update_period"><code>set_update_period</code></h3>
```c++
void  set_update_period (double period_s);
```

<p>Set the refresh period for the explorer. By default this value is set to 2 seconds.</p>

```c++
MulticastServiceExplorer explorer (0xefeefe89, 59150, 59169);

// very short update rate for unit tests
explorer.set_update_period (0.1);

explorer.process ();

[...]
```

<h3 id="member-function-process"><code>process</code></h3>
```c++
void  process ();
```

<p>Processes exploration. This function needs to be called regularly to let <code>MulticastServiceExplorer</code> do exploration. This function can be called often, as it only processes sockets when needed.</p>

<h3 id="member-function-begin"><code>begin</code></h3>
```c++
const_iterator begin ();
```

<p>Returns an iterator to the first session.</p>

<h3 id="member-function-end"><code>end</code></h3>
```c++
const_iterator end ();
```

<p>Returns an iterator to the end.</p>

<p><sup><a href="Mold.md">previous</a> | <a href="MulticastServiceProvider.md">next</a></sup></p>

