<p><sup><a href="undo.md">previous</a> | <a href="document.md">next</a></sup></p>

<h1>Threading System</h1>

<p>When programming with Flip, only one transaction can be started at one specific time. This does not allow for concurrent change on the model. However, Flip comes with a threading system that allow for concurrent change.</p>

<p>Threading in Flip allows to have multiple copies of the document (one per each Flip thread) and therefore concurrent change on those copies. Concurrent conflictual changes are resolved in the exact same way as for the server, so the client do not have to take care of it.</p>

<p>However threads in Flip are distinct from Operating System threads. Two flip threads can live in the same Operating System thread, in two different Operating System threads, and even in two Operating System processes.</p>

<p><sup><a href="undo.md">previous</a> | <a href="document.md">next</a></sup></p>

