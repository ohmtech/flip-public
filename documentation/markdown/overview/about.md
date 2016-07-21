<p><sup><a href="how.md">next</a></sup></p>

<h1>About Flip</h1>

<p>Flip is a data model library designed as a framework. It is real-time, collaboration-oriented, transactional, portable, and compact.</p>

<h2 id="keypoints">Key Points</h2>

<p>Flip features a number of key points which benefit your application:</p>

<ul>
<li>Real-time collaboration-oriented data model framework library</li>
<li>Single-user applications can be adapted to work with multiple users with no extra work</li>
<li>Undo/Redo and history are automatically handled (no action classes)</li>
<li>Copy/Paste can be done automatically, or refined to your needs</li>
<li>Multi-threaded/multi-process architecture</li>
<li>Transactional</li>
<li>Server side is limited to data model code, making it less prone to bugs</li>
<li>High stability</li>
<li>Performance oriented, extensible, and future-proof document formats</li>
<li>At the core of Ohm Studio's unrivaled collaboration solution</li>
</ul>

<p>Those key points are detailed below.</p>

<h2 id="prerequisites">Prerequisites</h2>

<ul>
<li>Client Development in C++</li>
<li>Portable C++ code (standard library, no external dependencies)</li>
<li>Apple XCode 6, Windows Microsoft Visual Studio C++ 2013 Update 4,    or 2015, GCC 4.8 with libstdc++ or Clang 3.6 with libc++ on Ubuntu 14.04</li>
</ul>

<h2 id="multi">Multi/single user, good practices</h2>

<p>The library has been conceived to let developers test their programs in a single-user context, but with the ability to easily adapt it for multiple users. Great effort has been made to minimize impact during the integration process. No server is required during development.</p>

<p>Moreover, our team set some good practices over the last few years to help you implement a solid architecture that will stand the test of time and be able to meet new needs.</p>

<p>In fact, we experienced that industrial implementation of the model yields the best correct-lines-to-total-lines ratio. The unique way that Flip works offers users the ability to do real-time collaboration without feeling any latency caused by the Internet.</p>

<h2 id="undo">Undo, redo, history, copy, paste</h2>

<p>Flip's very structure makes it unnecessary to manage undo and redo with specific code, which allows for the fast implementation of new industry-specific functionalities. The library can generate one or many undo/redo histories according to your needs.</p>

<p>Likewise, you can implement copy/paste with the same simplicity, while enjoying the unlimited possibilities of customization offered by this feature.</p>

<h2 id="format">Document format, document version, validation</h2>

<p>Flip supports a text-editable back-end writing format as well as a binary one. This has many advantages, including:</p>

<ul>
<li>Parsing the binary format is fast and portable</li>
<li>The ability to use a text editor in debug mode, which offers outstanding     readability with the text-editable back-end</li>
</ul>

<p>The use of a text editor in debug mode offers outstanding readability, even with documents weighing 100Mb+. It is simple and efficient, no matter how complex the model is.</p>

<p>The document works on its own version. Graphs of multiple versions are available (branches for A/B testing for instance). The document conversion system has been successfully tested in production environments, and even with radical paradigm changes.</p>

<p>Flip also allows you to set up a dynamic model validation system, regardless of the complexity involved. It can even handle structural model validation with no additional code. It doesn't generate orphan objects; in fact, none have been encountered in over 10 years of development.</p>

<h2 id="thread">Thread/Process Flip</h2>

<p>Using optimisic replication, Flip documents can be easily shared between threads or even processes without locks.</p>

<h2 id="interoperability">Interoperability</h2>

<p>Flip has been designed to integrate with external engines without imposing its own architecture. IDs, references, and any other system used by external engines can be integrated in Flip's engine, without the need to maintain specific glue code. Each Flip object can store multiple represented objects.</p>

<p>Flip's unique change detection system within a document lets client code parse the change in any direction to meet an external engine's object lifetime constraints.</p>

<p><sup><a href="how.md">next</a></sup></p>

