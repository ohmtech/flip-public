<p><sup><a href="simple.md">previous</a> | <a href="gesture2.md">next</a></sup></p>

<h1>Handling a Gesture</h1>

<p>This chapter shows to implement a simple gesture, that is an undo step that relates to multiple commits of the document.</p>

<h2 id="overview">Overview</h2>

<p>One common modifications of the document occurs over a gesture. That is, the actual modification of the document integrates multiple commits, but the undo step and publication to the outside world happens once the gesture is said to be "finished".</p>

<p>Example of such modifications are :</p>

<ul>
<li>Modifying the properties of an object using a mouse gesture</li>
</ul>

<p>The general idea of the modifications is that it spans over time. In this case the document is modified gradually as the gesture is performed. This allows on each commit to notify the observers so that the document views show an up-to-date of the document, even if this does not make the actual undo step stored in the history.</p>

<h2 id="impl">Implementation</h2>

<p>The following code illustrates a modification of the document such as a mouse gesture to change gradually the tempo of a song.</p>

```c++
Document document (Model::use (), 123456789UL, 'appl', 'gui ');
History <HistoryStoreMemory> history (document);
Song & song = document.root <Song> ();

[...]

song.tempo = 120.0;
document.commit ();           (1)

[...]

song.tempo = 130.0;
document.commit ();           (1)

[...]

song.tempo = 140.0;
document.commit ();           (1)

[...]

auto tx = document.squash (); (2)
history.add_undo_step (tx);   (3)
document.push ();             (4)
```

<ol>
<li>Modify the document gradually and commit to notify observer</li>
<li>Squash the push stack to make a single transaction out of the multiple commits</li>
<li>Store this resulting transaction in an undo step</li>
<li>Typically, the client of the library would advertise this document modification to       the outside world at that moment</li>
</ol>

<p>The next chapter, <a href="../history/gesture2.md">Handling a Non-deterministic Gesture</a> will show a strategy to use for undo/redo in the case of a more complex gesture.</p>

<p><sup><a href="simple.md">previous</a> | <a href="gesture2.md">next</a></sup></p>

