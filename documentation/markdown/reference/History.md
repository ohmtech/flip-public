<p><sup><a href="Float.md">previous</a> | <a href="Int.md">next</a></sup></p>

<h1>History Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/History.h</code></td></tr>
</table>

```c++
template <class HistoryStoreImpl>   class History;
```

<p><code>flip::History</code> is a flip compatible undo/redo stack implementation.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>HistoryStoreImpl</code></td><td>The type of history store, for example <code>HistoryStoreMemory</code>    or <code>HistoryStoreFile</code></td></tr>
</table>

<h2>Member Types</h2>

<table><tr><td><code>iterator</code></td><td>Bidirectional access iterator</td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Construct the <code>History</code></td></tr>
<tr><td><code><a href="#member-function-add_undo_step">add_undo_step</a></code></td><td>Add a new transaction on the undo stack</td></tr>
</table>

<h3>Iterators</h3>

<table><tr><td><code><a href="#member-function-begin">begin</a></code></td><td>Returns an iterator to the beginning</td></tr>
<tr><td><code><a href="#member-function-end">end</a></code></td><td>Returns an iterator to the end</td></tr>
<tr><td><code><a href="#member-function-last_undo">last_undo</a></code></td><td>Returns an iterator to last undo step</td></tr>
<tr><td><code><a href="#member-function-first_redo">first_redo</a></code></td><td>Returns an iterator to first redo step</td></tr>
</table>

<h3>Modifiers</h3>

<table><tr><td><code><a href="#member-function-clear">clear</a></code></td><td>Clears the contents</td></tr>
<tr><td><code><a href="#member-function-erase">erase</a></code></td><td>Erases element</td></tr>
<tr><td><code><a href="#member-function-execute_undo">execute_undo</a></code></td><td>Execute last undo step</td></tr>
<tr><td><code><a href="#member-function-execute_redo">execute_redo</a></code></td><td>Execute first redo step</td></tr>
</table>

<h3>Miscellaneous</h3>

<table><tr><td><code><a href="#member-function-version">version</a></code></td><td>Returns the history model version</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
template <class... Args>   History (DocumentBase & document, Args &&... args);
```

<p>Construct the <code>History</code> by attaching it to the document on which it shall operate. <code>args</code> are passed to the underlying <code>HistoryStoreImpl</code>.</p>

<h3 id="member-function-add_undo_step"><code>add_undo_step</code></h3>
```c++
void  add_undo_step (Transaction tx);
```

<p>Add a new transaction on the undo stack. The transaction might be empty or have no operations enabled in undo, in which case the operation is ignored.</p>

<h3 id="member-function-begin"><code>begin</code></h3>
```c++
iterator  begin ();
```

<p>Returns an iterator to the beginning of the history. If the history is empty, then the iterator returned is the same as the one returned by <code>end</code>.</p>

<h3 id="member-function-end"><code>end</code></h3>
```c++
iterator  end ();
```

<p>Returns an iterator to the end of the history, that is the element past the last element in the history.</p>

<h3 id="member-function-last_undo"><code>last_undo</code></h3>
```c++
iterator  last_undo ();
```

<p>Returns an iterator to last undo step of the history. If there is no last undo step, then the iterator returned is the same as the one returned by <code>end</code>.</p>

<h3 id="member-function-first_redo"><code>first_redo</code></h3>
```c++
iterator  first_redo ();
```

<p>Returns an iterator to first redo step of the history. If there is no first redo step, then the iterator returned is the same as the one returned by <code>end</code>.</p>

<h3 id="member-function-clear"><code>clear</code></h3>
```c++
void  clear ();
```

<p>Clears the contents of the history.</p>

<h3 id="member-function-erase"><code>erase</code></h3>
```c++
iterator  erase (iterator it);
```

<p>Erases history element at position <code>it</code>. Returns the <code>iterator</code> following <code>it</code>.</p>

<h3 id="member-function-execute_undo"><code>execute_undo</code></h3>
```c++
bool  execute_undo ();
```

<p>Executes the last undo step by replaying its associated transaction backward. Returns <code>true</code> if the transaction execution was successful, <code>false</code> otherwise.</p>

<h3 id="member-function-execute_redo"><code>execute_redo</code></h3>
```c++
bool  execute_redo ();
```

<p>Executes the first redo step by replaying its associated transaction forward. Returns <code>true</code> if the transaction execution was successful, <code>false</code> otherwise.</p>

<h3 id="member-function-version"><code>version</code></h3>
```c++
std::string  version ();
```

<p>Returns the history data model version at the moment of history creation. This is relevant only for history stores that provide persistence of history, like <code>HistoryStoreFile</code>.</p>

<p><sup><a href="Float.md">previous</a> | <a href="Int.md">next</a></sup></p>

