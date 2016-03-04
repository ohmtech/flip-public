<p><sup><a href="Ref.md">previous</a> | <a href="String.md">next</a></sup></p>

<h1>Signal Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Signal.h</code></td></tr>
</table>

```c++
template <uint32_t TYPE, class... Args>   class Signal;
```

<p><code>flip::Signal</code> is a type that allows signalling of flip objects in a type safe way.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>TYPE</code></td><td>A <code>uint32_t</code> unique number for the class of the object that represents the signal type</td></tr>
<tr><td><code>Args...</code></td><td>A variable number of arguments that compose the parameters of the signal</td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Signal</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Signal</code></td></tr>
<tr><td><code><a href="#member-function-operator %28%29">operator ()</a></code></td><td>Fire signal</td></tr>
<tr><td><code><a href="#member-function-connect">connect</a></code></td><td>Connect a listener</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Signal (Object & object);
```

<p>Constructor. Constructs the object by linking it to <code>object</code>.</p>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Signal ();
```

<p>Destructor.</p>

<h3 id="member-function-operator %28%29"><code>operator ()</code></h3>
```c++
void  operator () (Args... args);
```

<p>Notify all connection listeners for this <code>TYPE</code> of signal and this object as identified by its unique flip reference number.</p>

<p>All documents in the local document tree are also notified, and if the transport is configured to let those signal pass through, the server will be notified too.</p>

<h3 id="member-function-connect"><code>connect</code></h3>
```c++
template <class T, class F>   SignalConnection  connect (T & t, F f);   (1)
template <class F>   SignalConnection  connect (F f);                   (2)
```

<ol>
<li>function member delegate version</li>
<li>lambda version</li>
</ol>

<p>Connect a listener to this <code>Signal</code>. Returns a <code>SignalConnection</code>. This last type should be stored in a way to ensure that the listener could be signalled as long as the <code>SignalConnection</code> is alive.</p>

<p><sup><a href="Ref.md">previous</a> | <a href="String.md">next</a></sup></p>

