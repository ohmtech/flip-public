<p><sup><a href="DocumentServer.md">previous</a> | <a href="Entity.md">next</a></sup></p>

<h1>DocumentValidator Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/DocumentValidator.h</code></td></tr>
</table>

```c++
template <class T>   class DocumentValidator;
```

<p><code>flip::DocumentValidator</code> is the base of document validators.</p>

<h2>Template Parameters</h2>

<table><tr><td><code>T</code></td><td>The root class to validate. <code>T</code> must inherit from <code>flip::Object</code></td></tr>
</table>

<h2>Member Functions Synopsys</h2>

<table><tr><td><code><a href="#member-function-validate">validate</a></code></td><td>Receives document validation request notification</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-validate"><code>validate</code></h3>
```c++
virtual void   validate (T & root) = 0;
```

<p>To receive document change notification, one will inherit from this class and implement this function.</p>

<p>When a validation error is encountered, the function must throw to notify the flip system that validation failed. The macro <code>flip_VALIDATION_FAILED</code> is provided for convenience.</p>

<p>Example:</p>

```c++
class MyValidator : public flip::DocumentValidator <MyRootClass>
{
public:
   virtual void   document_changed (MyRootClass & root) override;
};

void  MyValidator::document_changed (MyRootClass & root)
{
   if (root.changed ())
   {
      if (root.tempo < 20.0) flip_VALIDATION_FAILED ("incorrect tempo");
   }
}
```

<p><sup><a href="DocumentServer.md">previous</a> | <a href="Entity.md">next</a></sup></p>

