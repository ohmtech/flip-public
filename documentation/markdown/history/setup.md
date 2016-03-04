<p><sup><a href="about.md">previous</a> | <a href="simple.md">next</a></sup></p>

<h1>Setting up the History</h1>

<p>This chapter the basic principle to setup an history for a document.</p>

<h2 id="overview">Overview</h2>

<p>History provides undo/redo features and more advanced ways to manipulate history. An history is a record of transactions to modify a document. Each transaction added to the history defines an <em>undo step</em>.</p>

<p>The <code>History</code> class provides this feature. It is linked to a document on which it will operate, but marking undo steps and manipulating history is done programatically.</p>

<p>A document might be managed by multiple <code>History</code>. An <code>History</code> will store each undo step using an history store. Some stores are volatile while some stores are persistent.</p>

<h2 id="ctor">Contructing an <code>History</code> instance</h2>

<p><code>History</code> are constructed by providing the document to which they are attached to. The <code>History</code> itself is a <code>template</code> and takes a template parameter which is the actual implementation of history store to use.</p>

<p>The following piece of code defines a volatile history for the document.</p>

```c++
#include "flip/History.h"
#include "flip/HistoryStoreMemory.h"

Document document (Model::use (), 123456789UL, 'appl', 'gui ');
History <HistoryStoreMemory> history (document);
```

<p>The following piece of code defines a persistent history for the document which survives the application life-span. The supplementary argument of the constructor is the path to the file which will store history.</p>

```c++
#include "flip/History.h"
#include "flip/contrib/HistoryStoreFile.h"

Document document (Model::use (), 123456789UL, 'appl', 'gui ');
History <HistoryStoreFile> history (document, "path/to/history");
```

<h2 id="basic">Basic Manipulation</h2>

<p>When you change the document, Flip will know that it was modified. Transactions represent the difference between two document states. When the document is modified, Flip internally keeps the old and new state of the document.</p>

<p>The history itself does not contain the whole state of the document, but rather the difference between two document states. In this way flip allows for a memory-performant managment of history.</p>

<p>The following piece of code shows how to add an undo step.</p>

```c++
Document document (Model::use (), 123456789UL, 'appl', 'gui ');
History <HistoryStoreMemory> history (document);

Song & song = document.root <Root> ();

song.tracks.emplace (song.tracks.end ());

auto tx = document.commit ();    (1)
history.add_undo_step (tx);      (2)

history.execute_undo ();         (3)
document.commit ();              (4)

history.execute_redo ();         (5)
document.commit ();
```

<ol>
<li>Commit the document and get the transaction representing the difference of states</li>
<li>Add this transaction as an undo step for the history</li>
<li>Execute undo, this puts the document back to the state before the first commit</li>
<li>The document is modified but not commited. This allows for more changes before commit</li>
<li>Execute redo, this puts the document back to the state after the first commit</li>
</ol>

<h2 id="disable">Disabling Part of the Document in Undo</h2>

<p>One might want to keep some actions as not part of the undo system. To do so one can mark objects to be not part of the undo system, so that Flip won't try to rollback their state during an undo.</p>

<p>Additionally, transactions which only contains operations on objects that are marked as not being part of the undo system will be ignored by the history system.</p>

<p>The following piece of code shows how to disable an object from undo.</p>

```c++
class UserData : public Object {
public:
   Float scroll_position_x;
   Float scroll_position_y;
};


Document document (Model::use (), 123456789UL, 'appl', 'gui ');
History <HistoryStoreMemory> history (document);

Song & song = document.root <Root> ();

song.user_data.disable_in_undo ();        (1)

song.user_data.scroll_position_x = 120;
song.user_data.scroll_position_y = 140;

auto tx = document.commit ();
history.add_undo_step (tx);               (2)

song.tracks.emplace (song.tracks.end ());
song.user_data.scroll_position_x = 100;
song.user_data.scroll_position_y = 100;

tx = document.commit ();
history.add_undo_step (tx);               (3)

history.execute_redo ();                  (4)
document.commit ();
```

<ol>
<li>Disabling propagates to the object subtree, including <code>scroll_position_x</code> and <code>scroll_position_y</code></li>
<li>The transaction is therefore empty as seen from the History point of view. No undo point is created.</li>
<li>The transaction is seen as only a track add from the History point of view.</li>
<li>Therefore at this stage, the track is removed but the <code>scroll_position_*</code> value is <code>100</code></li>
</ol>

<p>Disabling is a property evaluated at <code>commit</code> time. It is possible to change the undo recording state of an object and its subtree dynamically, using the respective <code>disable_in_undo</code> and <code>inherit_in_undo</code> appropriately.</p>

<h2 id="visitor">Visiting the History</h2>

<p>The <code>History</code> can be seen as a container of transactions. As such, <code>History</code> provides the functions <code>begin</code> and <code>end</code> which allows to iterate through the history to discover transactions.</p>

<p><code>History</code> also provides the function member <code>last_undo</code> which points to the last undo step, that is the transaction executed when <code>execute_undo</code> is called.</p>

<p>Similarly, <code>History</code> also provides the function member <code>first_redo</code> which points to the first redo step, that is the transaction executed when <code>execute_redo</code> is called.</p>

<p>As such, iterating from <code>begin</code> to <code>end</code> will cover the all history, and the iterators <code>last_undo</code> and <code>first_redo</code> are in the history as long as an undo step exists or a redo step exists.</p>

<p>This architecture allows to provide an history browser, but also to modify the transactions in the history. This technique can be useful in a variety of situations which will be exposed in a later chapter of this book.</p>

<h2 id="write">Rewriting History</h2>

<p><code>History</code> allows to be rewritten which can be useful in some situations. <code>History</code> provides the function member <code>erase</code> to remove a specific transaction from the history.</p>

<p>The next chapter, <a href="../history/simple.md">Handling a Simple Modification</a> will show a strategy to use for undo/redo in the immediate case.</p>

<p><sup><a href="about.md">previous</a> | <a href="simple.md">next</a></sup></p>

