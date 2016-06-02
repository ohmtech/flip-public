<p><sup><a href="Ref.md">previous</a> | <a href="String.md">next</a></sup></p>

<h1>Signal Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Signal.h</code></td></tr>
</table>

```c++
template <class... Args>   class Signal;
```

<p><code>flip::Signal</code> is a type that allows signalling of flip objects in a type safe way.</p>

<p>Signals are only local and targetted at an object. They are not broadcasted to the other clients in a collaboration case, and they are not part of an observer. It is therefore not part of the document model.</p>

<p>However, if multiple documents are using a <code>Hub</code> on a local machine in different threads or processes, the signal will be delivered on the local machine.</p>

<p><code>Signal</code>s can also be a way to communicate directly with the server.</p>

<p>When messages should be part of a document model and broadcasted then <a href="../reference/Message.md"><code>Message</code></a> shall be used instead.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>Args...</code></td><td>A variable number of arguments that compose the parameters of the signal</td></tr>
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
Signal (uint32_t type, Object & object);
```

<p>Constructor. Constructs the object by linking it to <code>object</code>. <code>type</code> is a unique number for the class of the object that represents the signal type.</p>

<p>Example :</p>

```c++
class Form : public Object
{
public:
   enum
   {
      Signal_OPEN_VIEW = 0,
      Signal_CLOSE_VIEW,
   };

   Form ()
   : signal_open_view (Signal_OPEN_VIEW, *this)
   , signal_close_view (Signal_CLOSE_VIEW, *this)

   Signal <int /* width */, int /* height */> signal_open_view;
   Signal <> signal_close_view;

};
```

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Signal ();
```

<p>Destructor.</p>

<h3 id="member-function-operator %28%29"><code>operator ()</code></h3>
```c++
void  operator () (Args... args);
```

<p>Notify all connection listeners for this <code>type</code> of signal and this object as identified by its unique flip reference number.</p>

<p>All documents in the local document tree are also notified, and if the transport is configured to let those signal pass through, the server will be notified too.</p>

```c++
form.signal_open_view (1280, 1024);
form.signal_close_view ();
```

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

```c++
SignalConnection cnx = form.signal_open_view.connect ([](int width, int height){
   // open view witdh x height
});

SignalConnection cnx2 = form.signal_close_view.connect ([](){
   // close view
});
```

<p>Note that <code>cnx</code> and <code>cnx2</code> in the above example needs to be stored. If they go below the function scope, they will be destroyed and therefore the signal connection will be broken.</p>

<p><code>SignalConnections</code> cannot be copied, but can be moved with <code>std::move</code>.</p>

<p><sup><a href="Ref.md">previous</a> | <a href="String.md">next</a></sup></p>

