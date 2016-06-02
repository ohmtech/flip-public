<p><sup><a href="thread.md">previous</a></sup></p>

<h1>Document Format, Conversion</h1>

<p>Flip provides an unique document format. Document versions are maintained so that it allows document from different versions to be converted to some other version. Convenient classes are provided for the latter to simplify work.</p>

<h2 id="format">Document Format</h2>

<p>Flip comes with 2 document formats, a fast binary one for production and a textual one for debugging. Should they need it, clients of the library can also write their own document format.</p>

<h2 id="format">Conversion</h2>

<p>The client provides a version tree, and how to transition from one version format to another. This way, a complex version system can be easily maintained, allowing even A/B testing.</p>

<p><sup><a href="thread.md">previous</a></sup></p>

