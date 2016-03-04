<p><sup><a href="overview.md">previous</a> | <a href="using.md">next</a></sup></p>

<h1>Language Reference</h1>

<p>This chapter describes the Utml language in pseudo notation format.</p>

<h2 id="common">Common elements</h2>

<p>The following describes common elements used below.</p>

<h3 id="common-skip">Skip character</h3>

<p>For every rule except when parsing the value of a blob, the skip character set are white spaces <code>space</code>, <code>tab</code>, <code>cr</code>, <code>lf</code>. This means in particular that an expression, except for blob value, might be spanned on multiple lines. In the following it will be assumed that symbols are separated by the skip character when matching a rule.</p>

<h3 id="common-class">Class name</h3>

```
<class-name>
```

<p><code><class-name></code> represents a class name as declared in Flip. It follows Flip class name validation.</p>

<h3 id="common-member">Member name</h3>

```
<member-name>
```

<p><code><member-name></code> represents an object member name as declared in Flip. It follows Flip object name validation.</p>

<h2 id="document">Document</h2>

<p>Document contains exactly one top level object, which represent the root of the document tree.</p>

```
<document> = <top-level-object>
```

<h2 id="top">Top level objects</h2>

<p>Top level objects are objects like the root object and every objects stored in a Flip container like <code>Array</code> or <code>Collection</code>.</p>

```
<top-level-object> = <top-identifier> <content>
<top-identifier> = <class-name> [object-name]
```

<p>A top level object has an <em>optional</em> name to be used with <code>ObjectRef</code> references.</p>

<h2 id="content">Content</h2>

```
<content> = "{" 0*<member-definition> "}"
<member-definition> = <member-name> "=" <value>
```

<p>The content of an object may contain zero or more member definition. This content may be used recursively as seen in the value defined below.</p>

<h2 id="value">Value</h2>

<p>The value type is dependent of the associated data model. As Flip read the Utml source, it will match it to the provided data model.</p>

<p>When a member definition is omited, the equivalent member definition is then implicitely defaulted. The default values are described below.</p>

<h3 id="value-bool"><code>Bool</code></h3>

```
<value> = "true" | "false"
```

<p>Default value is <code>false</code>.</p>

<h3 id="value-int"><code>Int</code></h3>

<p><code>value</code> represents an integer compatible with <code>std::sscanf</code> with the <code>"%lld"</code> format specifier.</p>

<p>Default value is <code>0</code>.</p>

<h3 id="value-float"><code>Float</code></h3>

<p><code>value</code> represents an integer compatible with <code>std::sscanf</code> with the <code>"%lf"</code> format specifier.</p>

<p>Default value is <code>0.0</code>.</p>

<h3 id="value-object"><code>ObjectRef</code></h3>

```
<value> = <object-name> 0*("." <member-name>)
```

<p>Default value is a <code>Ref::null</code> Flip reference.</p>

<h3 id="value-blob"><code>Blob</code> or <code>String</code></h3>

```
<value> = <value-string> | <value-hex> | <value-base64>
<value-string> = '"' <escaped-ascii> '"'
<value-hex> = "0x" <hexadecimal>
<value-base64> = "decode_b64" "(" <base64> ")"
```

<ul>
<li><code><escaped-ascii></code> represents data parsable by <code>BackEndMlCodec::decode_escaped_ascii</code></li>
<li><code><hexadecimal></code> represents data parsable by <code>BackEndMlCodec::decode_hexadecimal</code></li>
<li><code><base64></code> represents data parsable by <code>BackEndMlCodec::decode_base64</code></li>
</ul>

<p>Default value is an empty <code>Blob</code>.</p>

<h3 id="value-collection"><code>Collection</code></h3>

```
<value> = "{" 0*<top-level-object> "}"
```

<p>Default value is an empty <code>Collection</code>.</p>

<h3 id="value-array"><code>Array</code></h3>

```
<value> = "{" 0*<top-level-object> "}"
```

<p>Default value is an empty <code>Array</code>.</p>

<h3 id="value-array"><code>Object</code> member</h3>

```
<value> = "{" 0*<member-definition> "}"
```

<p>Default value is an object which all members definition are defaulted, recursively.</p>

<h3 id="value-message"><code>Message</code></h3>

<p>Message cannot be defined because they don't have a value.</p>

<p><sup><a href="overview.md">previous</a> | <a href="using.md">next</a></sup></p>

