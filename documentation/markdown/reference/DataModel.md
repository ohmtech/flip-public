<p><sup><a href="DataConsumerMemory.md">previous</a> | <a href="DataProviderFile.md">next</a></sup></p>

<h1>DataModel Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/DataModel.h</code></td></tr>
</table>

```c++
template <class T>   class DataModel;
```

<p><code>flip::DataModel</code> is a type that represents declarations of classes that form a consistent data model. Typical usage consists to derive from this class, using this class as the template parameter, to define your model.</p>

<p>Example:</p>

```c++
class MyModel : public flip::DataModel <MyModel> {};
```

<h2>Member Functions Synopsys</h2>

<table><tr><td><code><a href="#member-function-version">version</a></code></td><td>Sets the format revision of the data model</td></tr>
<tr><td><code><a href="#member-function-declare">declare</a></code></td><td>Declares a class of the model</td></tr>
<tr><td><code><a href="#member-function-add">add</a></code></td><td>Adds a class to the model</td></tr>
<tr><td><code><a href="#member-function-set_root">set_root</a></code></td><td>Changes the root class of the model</td></tr>
<tr><td><code><a href="#member-function-has">has</a></code></td><td>Returns true iff the class is available in the model</td></tr>
<tr><td><code><a href="#member-function-clone_from">clone_from</a></code></td><td>Clones an entire model</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-version"><code>version</code></h3>
```c++
static void version (const std::string & version);
```

<p>Sets the format revision of the data model. The name must be in the <code>ascii-7</code> character set, with exception of control characters as well as <code>del</code> character.</p>

<p>The format revision is used to discriminate between two data models. This is typically used for document conversion from one data model to another one, for example when upgrading to a new version of the model with more properties.</p>

<p>Example:</p>

```c++
MyModel::version ("1.00 RC1");
```

<h3 id="member-function-declare"><code>declare</code></h3>
```c++
template <class U> static Class <U> &  declare ();
```

<p>Declares a class and add it to the model. Returns a reference to the <code>Class</code> to declare the class name, inheritance and members.</p>

<p>This also sets the class as the root class model, making the last declaration the root class by default. This behavior can be changed by using <code>set_root</code> decribed below.</p>

<p>Example:</p>

```c++
MyModel::declare <MyClass> ()
   .name ("MyClass");
```

<h3 id="member-function-add"><code>add</code></h3>
```c++
template <class U> static void  add ();
```

<p>Add an already declared class to the model. This is typically used when sharing a class between multiple models.</p>

<p>Example:</p>

```c++
MyModel::declare <MyClass> ()
   .name ("MyClass");

MyModel2::add <MyClass> ();
```

<h3 id="member-function-set_root"><code>set_root</code></h3>
```c++
template <class U> static void  set_root ();
```

<p>Changes the root class of the model. The class must already been declared in the model. This is typically used in unit testing.</p>

<p>Example:</p>

```c++
MyModel::declare <Root> ()
   .name ("Root");
// last declared class is root by default

MyModel::set_root <MyClass> ();
// now the root of 'MyModel' is 'MyClass'
```

<h3 id="member-function-has"><code>has</code></h3>
```c++
template <class U> static bool  has ();
```

<p>Returns true iff the class is available in the model.</p>

<p>Example:</p>

```c++
MyModel::declare <MyClass> ()
   .name ("MyClass");

assert (MyModel::has <MyClass>);
```

<h3 id="member-function-clone_from"><code>clone_from</code></h3>
```c++
template <class Model> static void  clone_from ();
```

<p>Clones an entire model.</p>

<p>This is typically used in unit testing to :</p>

<ul>
<li>clone an entire model and change the root class to isolate testing</li>
<li>clone an entire model and add a text fixture class</li>
</ul>

<p>Example:</p>

```c++
MyTestModel::clone_from <MyModel> ();
MyTestModel::declare <MyFixture> ();
MyTestModel::set_root <MyFixture> ();
```

<p><sup><a href="DataConsumerMemory.md">previous</a> | <a href="DataProviderFile.md">next</a></sup></p>

