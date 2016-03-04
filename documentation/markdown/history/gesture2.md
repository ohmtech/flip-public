<p><sup><a href="gesture.md">previous</a></sup></p>

<h1>Handling a Non-deterministic Gesture</h1>

<p>This chapter shows to implement a more complex gesture, that is an undo step that relates to multiple commits of the document when the end of the gesture cannot be known <em>a priori</em>.</p>

<h2 id="overview">Overview</h2>

<p>One common modifications of the document occurs over a gesture. That is, the actual modification of the document integrates multiple commits, but the undo step and publication to the outside world happens once the gesture is said to be "finished".</p>

<p>Sometimes however, the "finished" state of a transaction cannot be determined <em>a priori</em>. This means that the user of the application might expect the last undo to extend over time, based on certain criteria.</p>

<p>Example of such modifications are :</p>

<ul>
<li>Modifying the properties of an object using the keyboard arrows, and wanting the undo action to revert all last keyboard actions</li>
</ul>

<p>The general idea of the modifications is that it spans over time. In this case the document is modified gradually as the gesture is performed. This allows on each commit to notify the observers so that the document views show an up-to-date of the document, even if this does not make the actual undo step stored in the history.</p>

<p>The undo step itself will be stored at each commit, like the simple undo case. However, this last undo step will be replaced as new actions are performed. For example, if the user moves an object on screen using the keyboard arrows 4 times, then the last undo is replaced with the equivalent full transaction representing the change from the very start. The user would then expect the undo action to revert its 4 actions to be reverted in one-step instead of each action.</p>

<h2 id="impl">Implementation</h2>

<p>The following code illustrates such a modification of the document to change gradually the tempo of a song.</p>

```c++
Document document (Model::use (), 123456789UL, 'appl', 'gui ');
History <HistoryStoreMemory> history (document);
Song & song = document.root <Song> ();

[...]

song.tempo = song.tempo + 10.0;  (1)
auto tx = document.commit ();    (2)
history.add_undo_step (tx);      (3)

[...]

song.tempo = song.tempo + 10.0;  (4)
document.commit ();
auto tx = document.squash ();    (5)
*history.last_undo () = tx;      (6)

[...]

song.tempo = song.tempo + 10.0;  (4)
document.commit ();
auto tx = document.squash ();    (5)
*history.last_undo () = tx;      (6)

[...]

document.push ();                (7)
```

<ol>
<li>After a keyboard event, increment the tempo by 10 bpm</li>
<li>Commit the change</li>
<li>Make a new undo step with this transaction</li>
<li>Increment the tempo by 10 bpm</li>
<li>Squash the push stack to make a single transaction out of the multiple commits</li>
<li>Replace the last undo step with the resulting transaction</li>
<li>At some point, the client of the library would advertise this document modification to       the outside world at that moment (for example when starting a new action)</li>
</ol>

<p><sup><a href="gesture.md">previous</a></sup></p>

