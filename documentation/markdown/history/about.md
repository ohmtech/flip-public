<p><sup><a href="setup.md">next</a></sup></p>

<h1>About Flip History Strategy Guide</h1>

<p>This guide is a serie of guides indented for flip developers to assist into different strategies to provide History/Undo/Redo features.</p>

<h2 id="how">How to Use This Document</h2>

<p>If you want to add flip undo/redo support to your application, first read <a href="../guide/README.md">Flip Programming Guide</a> to have a taste of the features that flip can add to your application.</p>

<p>You don't necesseraly need to read each chapter of this manual. Chapters are separated in very specific tasks, for a very specific need.</p>

<h2 id="requisites">Prerequisites</h2>

<p>You should be familiar with C++ programming, especially templates. You should be also familiar with basic C++ design patterns such as the Singleton or Delegate pattern.</p>

<p>You should be familiar with the MVC design pattern. In a flip managed application, flip acts as the Model part of the MVC design pattern.</p>

<h2 id="seealso">See Also</h2>

<p>See <a href="../reference/README.md">Flip Framework Reference</a> for details on Flip classes.</p>

<h2 id="content">Content</h2>

<p>This guide presents the following content in a didactic order.</p>

<ul>
<li>The chapter <a href="../history/setup.md">Setting up the History</a> exposes       the basic setup of the History object</li>
<li>The chapter <a href="../history/simple.md">Handling a Simple Modification</a>       shows a first simple case to record an undo step</li>
<li>The chapter <a href="../history/gesture.md">Handling a Gesture</a>       shows how to record history when the modifications span over time</li>
<li>The chapter <a href="../history/gesture2.md">Handling a Non-deterministic Gesture</a>       shows how to record history when the modifications span over time       with a more complex scenario</li>
</ul>

<p>This guide is intended to be read in its natural chapter order. The first chapter, <a href="../history/setup.md">Setting up the History</a> will guide you through the task of setting up an history to be used with a document.</p>

<p><sup><a href="setup.md">next</a></sup></p>

