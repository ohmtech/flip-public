<p><sup><a href="setup.md">previous</a> | <a href="gesture.md">next</a></sup></p>

<h1>Handling a Simple Modification</h1>

<p>This chapter shows to implement a simple undo, that is an undo step that relates to a single commit of the document.</p>

<h2 id="overview">Overview</h2>

<p>Some common modifications of the document are one-shot. That is, the actual modification of the document, its commit and publication to the outside world happens once in a row.</p>

<p>Example of such modifications are :</p>

<ul>
<li>Toggling a parameter value</li>
<li>Editing a parameter value textually</li>
<li>Modifying a document from a menubar item</li>
</ul>

<p>The general idea of the modification is that they are punctual events, that is they don't span over time. An example of modification that does not fall in this category would be for example modification that comes from a mouse gesture, where the document is modified gradually as the gesture is performed.</p>

<h2 id="impl">Implementation</h2>

<p>The following code illustrates a modification of the document such as a menu item used to insert a track in a song.</p>

```c++
Document document (Model::use (), 123456789UL, 'appl', 'gui ');
History <HistoryStoreMemory> history (document);

Song & song = document.root <Song> ();

song.tracks.emplace (song.tracks.end ());

auto tx = document.commit ();    (1)
history.add_undo_step (tx);      (2)
document.push ();                (3)
```

<ol>
<li>In this case, the modification is simply a single commit</li>
<li>Add this modification as an undo step</li>
<li>Typically, the client of the library would advertise this document modification to       the outside world at that moment</li>
</ol>

<p>The next chapter, <a href="../history/gesture.md">Handling a Gesture</a> will show a strategy to use for undo/redo in the case of a gesture.</p>

<p><sup><a href="setup.md">previous</a> | <a href="gesture.md">next</a></sup></p>

