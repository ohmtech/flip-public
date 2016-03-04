<p><sup><a href="String.md">previous</a> | <a href="Variant.md">next</a></sup></p>

<h1>Transaction Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/Transaction.h</code></td></tr>
</table>

```c++
class Transaction;
```

<p><code>flip::Transaction</code> is a type that allows signalling of flip objects in a type safe way.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>TYPE</code></td><td>A <code>uint32_t</code> unique number for the class of the object that represents the signal type</td></tr>
<tr><td><code>Args...</code></td><td>A variable number of arguments that compose the parameters of the signal</td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>Transaction</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>Transaction</code></td></tr>
<tr><td><code><a href="#member-function-clear">clear</a></code></td><td>Empty the transaction</td></tr>
<tr><td><code><a href="#member-function-empty">empty</a></code></td><td>Returns <code>true</code> <em>iff</em> the transaction contains at least one instruction</td></tr>
<tr><td><code><a href="#member-function-serialize">serialize</a></code></td><td>Generate data from the transaction</td></tr>
<tr><td><code><a href="#member-function-push">push</a></code></td><td>Concatenate a transaction to this transaction</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
Transaction ();                                    (1)
Transaction (const Transaction & rhs);             (2)
Transaction (Transaction && rhs);                  (3)
Transaction (const std::vector <uint8_t> & data);  (4)
```

<ol>
<li>Default constructor, constructs an empty transaction.</li>
<li>Copy constructor. Constructs the transaction with copy of <code>other</code>.</li>
<li>Move constructor. Constructs the transaction by moving <code>other</code>.</li>
<li>Constructor. Constructs the transaction from data previously produce by <code>serialize</code>.</li>
</ol>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~Transaction ();
```

<p>Destructor.</p>

<h3 id="member-function-clear"><code>clear</code></h3>
```c++
void  clear ();
```

<p>Empty the transaction and its metadata.</p>

<h3 id="member-function-empty"><code>empty</code></h3>
```c++
bool  empty () const;
```

<p>Returns <code>true</code> <em>iff</em> the transaction contains at least one instruction.</p>

<h3 id="member-function-serialize"><code>serialize</code></h3>
```c++
std::vector <uint8_t>   serialize () const;
```

<p>Generate data from the transaction. This data can be stored everywhere or send over a network. The data contains the transaction instructions as well as metadata.</p>

<h3 id="member-function-push"><code>push</code></h3>
```c++
Transaction &  push (Transaction && tx);
```

<p>Concatenate transaction <code>tx</code> to this transaction by moving <code>tx</code>.</p>

<p><sup><a href="String.md">previous</a> | <a href="Variant.md">next</a></sup></p>

