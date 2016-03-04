<p><sup><a href="Document.md">previous</a> | <a href="DocumentServer.md">next</a></sup></p>

<h1>DocumentObserver Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/DocumentObserver.h</code></td></tr>
</table>

```c++
template <class T>   class DocumentObserver;
```

<p><code>flip::DocumentObserver</code> is the base of document observers.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>T</code></td><td>The root class to observer. <code>T</code> must inherit from <code>flip::Object</code></td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><code><a href="#member-function-document_changed">document_changed</a></code></td><td>Receives document change notification</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-document_changed"><code>document_changed</code></h3>
```c++
virtual void   document_changed (T & root) = 0;
```

<p>To receive document change notification, one will inherit from this class and implement this function. This function is then trigerred at <code>commit</code> or <code>pull</code> stage.</p>

<p>Example:</p>

```c++
class MyObserver : public flip::DocumentObserver <MyRootClass>
{
public:
   virtual void   document_changed (MyRootClass & root) override;
};

void  MyObserver::document_changed (MyRootClass & root)
{
   if (root.changed ())
   {
      // ...
   }
}
```

<p><sup><a href="Document.md">previous</a> | <a href="DocumentServer.md">next</a></sup></p>

