<p><sup><a href="undo.md">previous</a> | <a href="document.md">next</a></sup></p>

<h1>Threading System</h1>

<p>When programming with Flip, only one transaction can be started at a time. This does not allow for concurrent changes of the model. However, Flip comes with a threading system that allows for concurrent modifications.</p>

<p>Threading in Flip allows one to have multiple copies of the document (one per each Flip thread), and therefore concurrently change those copies. Conflicting concurrent changes are resolved in the exact same way as they are on the server, so the client does not have to take care of this.</p>

<p>However, threads in Flip are different than operating system threads. Two Flip threads can live in the same operating system thread, in multiple operating system threads, and even in multiple operating system processes.</p>

<p><sup><a href="undo.md">previous</a> | <a href="document.md">next</a></sup></p>

