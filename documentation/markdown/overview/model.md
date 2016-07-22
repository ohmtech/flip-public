<p><sup><a href="how.md">previous</a> | <a href="undo.md">next</a></sup></p>

<h1>Interfacing with the Model</h1>

<p>When interfacing with the model, the code can be separated in two parts:</p>

<ol>
<li>the part that control the model</li>
<li>the part that reacts to model changes</li>
</ol>

<h2 id="control">Controlling the Model</h2>

<p>Controlling the model is done by directly changing the model, just as you would do with regular classes.</p>

<p>If a class <code>Element</code> has two members <code>position</code> and <code>length</code>, changing the position and the length of the element is as simple as:</p>

```c++
element.position = some_position;
element.length = some_length;
```

<p>The members used by classes are actually Flip objects. They are proxies which handle changes to the model.</p>

<p>For example, to write a class with a member:</p>

```c++
int	position;
```

<p>You would transform it to:</p>

```c++
flip::Int64	position;
```

<p>And to write a class with a list of members:</p>

```c++
std::list<Element>	element_arr;
```

<p>You would transform it to:</p>

```c++
flip::Array<Element> element_arr;
```

<p>Manipulating Flip containers is very close to the conventions used by the C++ standard library (STL). Adding an element is done with <code>insert</code>, and erasing an element is done with <code>erase</code>. Other functions are provided in a monolithic way like in the original STL in order to ensure that developers will feel right at home.</p>

<h2 id="view">Observing the Model</h2>

<p>When a client modifies its own model or receives a modification (transaction) of the model from another client from the server, the model is directly modified.</p>

<p>The client of the model will have registered one or more observers to be notified when the model changes. These observer are called with the model's root object passed as a argument.</p>

<p>When the client observer is called, Flip maintains the previous version of the model as well as the current one as applied by the transaction. This allows the client to know:</p>

<ul>
<li>exactly which objects were modified</li>
<li>the value of an object before the modification</li>
<li>what was inserted/erased from a container</li>
<li>what was moved from one container to another</li>
</ul>

<p><center><img src="model.png" /></center></p>

<p>The client is then responsible for parsing the model tree to ensure that its local representation of the model matches the one from Flip.</p>

<p>Furthermore, Flip was designed to make this task as simple as possible. The model tree can be parsed in any direction, parsed multiple times, and so on. Multiple represented objects can also be attached to Flip objects. We have also supplied some code patterns that can simplify your work.</p>

<p>As long as the model client does not exit during the observer callback, Flip still maintains the old and current versions of the model. Each Flip object, as well as your custom classes, have an <code>added()</code> method which can be called to see if an object or its compound objects have been modified. This call is also recursive.</p>

<p>Whether your local model uses object pointers, references, or IDs, you can attach it to any Flip object. This architecture offers simple but powerful interoperability with Flip and your GUI or external libraries.</p>

<p><sup><a href="how.md">previous</a> | <a href="undo.md">next</a></sup></p>

