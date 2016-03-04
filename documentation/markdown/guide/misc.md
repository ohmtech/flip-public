<p><sup><a href="remote.md">previous</a></sup></p>

<h1>More Fun with Flip</h1>

<h2 id="history">Providing Undo/Redo Feature</h2>

<p>Flip provides an undo/redo history system.</p>

```c++
void  run ()
{
   Document document (Model::use (), 123456789ULL, 'acme', 'gui ');
   History history (document);                                       (1)

   Root & root = document.root <Root> ();

   root.happiness_level = 100.0;

   document.set_label ("Change");                                    (2)

   auto tx = document.commit ();                                     (3)

   history.push (tx);                                                (4)

   history.undo ().execute ();                                       (5)
   history.redo ().execute ();                                       (6)
}
```

<ol>
<li>Set up a history for document</li>
<li>Set a label for the forming transaction</li>
<li><code>commit</code> returns a transaction, which has the label as a metadata</li>
<li>push the transaction to the history system</li>
<li>undo the transaction</li>
<li>redo the transaction</li>
</ol>

<h2 id="manipulation">Manipulating Transactions</h2>

<p>Transactions represent exactly the difference between to state of the document. Flip flexibility allows to store them, and replay them in any direction.</p>

```c++
void  run ()
{
   Document document (Model::use (), 123456789ULL, 'acme', 'gui ');

   Root & root = document.root <Root> ();

   assert (root.tempo == 0.0);            (1)

   root.tempo = 100.0;

   auto tx = document.commit ();

   document.execute_backward (tx);        (2)
   document.execute_forward (tx);         (3)
}
```

<ol>
<li>All flip values are constructed with a zero value or an empty state</li>
<li>play the transaction backward, happiness goes back to 0.0. Note that the transaction is applied, but the document is not commited</li>
<li>play the transaction backward, happiness goes back to 100.0. Note that the transaction is applied, but the document is not commited. If it was commited, it would produce an empty transaction.</li>
</ol>

<p>Since transactions can be copied and are just data without external coupling, they can be used for many usual kind of problem solving.</p>

<h2 id="io">Reading/Writing a Document</h2>

<p>Flip supports two formats :</p>

<ul>
<li>A binary format with optimal performance and secure enough for production use,</li>
<li>A markup language format, human readable and editable, for debugging purposes</li>
</ul>

<p>Those two backend formats can be read or written in an infinite number of media using a traditional Consumer/Producer architecture.</p>

<h3 id="io-write">Writing a Document</h3>

```c++
void  write ()
{
   BackEndIR backend = document.write ();       (1)

   std::vector <uint8_t> data;
   DataConsumerMemory consumer (data);          (2)

   backend.write <BackEndBinary> (consumer);    (3)
}
```

<ol>
<li>Write the document into an intermediate representation format. This format is also used to do document revision conversion</li>
<li>Set up a data consumer which will write in memory</li>
<li>Write to the consumer using the binary format</li>
</ol>

<h3 id="io-read">Reading a Document</h3>

```c++
void  read ()
{
   std::vector <uint8_t> data;                  (1)
   DataProviderMemory provider (data);          (2)

   BackEndIR backend;
   backend.register_backend <BackEndBinary> (); (3)
   backend.register_backend <BackEndMl> ();

   backend.read (provider);                     (4)
}
```

<ol>
<li>Here we suppose that data is already filled with document data</li>
<li>Attach a provider to the data to read</li>
<li>Register the two formats that the backend can read. The backends implementation are able to tell if the incoming data is in the right format</li>
<li>Read the document</li>
</ol>

<p><sup><a href="remote.md">previous</a></sup></p>

