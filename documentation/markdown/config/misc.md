<p><sup><a href="dll.md">previous</a> | <a href="msvc.md">next</a></sup></p>

<h1>Miscellaneous Configuration</h1>

<p>This chapter describes several preprocessor macros used to change specific behavior of the Flip framework.</p>

<h2 id="fatal"><code>flip_FATAL_MODE</code></h2>

<p>When the Flip framework encounters an operation that put its state to subsequent undefined behavior, it will general a fatal error. The <code>flip_FATAL_MODE</code> will control how this fatal error is generated. It is for example used when the framework is able to detect an incorrect use of its API.</p>

<ul>
<li>if set to <code>flip_FATAL_MODE_ABORT</code>, the Flip framework will trigger    an abortion on debug and will throw on release, which is most likely desired when developping.    <em>This is the default behavior</em></li>
<li>if set to <code>flip_FATAL_MODE_THROW</code>, the Flip framework will throw.    This is used in unit testing to ensure that programmers error can be    reliably detected</li>
<li>if set to <code>flip_FATAL_MODE_USER</code>, the <code>flip_FATAL</code> macro    has to be defined by the user in some appropriate way.</li>
</ul>

<p>One will activate one option or another using the processor macros or definitions. For example :</p>

```
flip_FATAL_MODE=flip_FATAL_MODE_THROW
```

<p><code>flip_FATAL</code> can be defined in a user specific way.  To do this define <code>flip_FATAL_MODE</code> to <code>flip_FATAL_MODE_USER</code> and provide a definition of it using a compiler option.  The best way though is to provide a user config file <code>flip_user_config.h</code> somewhere in the header search path of the compiler and define <code>flip_HAS_FLIP_USER_CONFIG_H</code>.</p>

<p>For example such a <code>flip_user_config.h</code> could look like this:</p>

```
#pragma once

#include <cassert>

extern void trace_error(char* msg);

#define flip_FATAL { trace_error("FATAL!"); assert(false); throw; }
```

<blockquote><h6>Important</h6> Since <code>flip_FATAL</code> is used as a terminate function, the implementation must make sure that it is never returning.  The <code>throw</code> in the example above ensures this.</blockquote>

<h2 id="nothing"><code>flip_NOTHING</code></h2>

<p>Values such as <code>Int</code>, <code>Float</code> or <code>Blob</code> in the flip framework may have conceptually "no value" at specific object life cycles.</p>

<ul>
<li>if a value is <code>added</code> then its <code>before</code> value is "no value",</li>
<li>if a value is <code>removed</code> then its <code>value</code> is "no value".</li>
</ul>

<p>Flip provides two way to represents this value :</p>

<ul>
<li>either by implicitely considering that the "no value"    is defined and explicitely <code>0</code> for numbers or empty for dynamic sized data,    using <code>flip_NOTHING_ZERO</code>,    <em>This is the default behavior</em>,</li>
<li>either considering "no value" to be an error    and <code>flip_FATAL</code> when attempting to access it,    using <code>flip_NOTHING_FATAL</code>.</li>
</ul>

<p>One will activate one option or another using the processor macros or definitions. For example :</p>

```
flip_NOTHING=flip_NOTHING_FATAL
```

<h2 id="entityuse"><code>flip_ENTITY_USE</code></h2>

<p>The flip Framework <code>Entity</code> system allows to bind an arbitraty object to a flip <code>Object</code> or <code>Type</code>. The system itself is type safe and memory leak safe. However if one does not erase from the <code>Entity</code> an object it previously emplaced, there is no way for the client of the Flip framework to exactly monitor when the underlying object is going to be effectively freed.</p>

<p>For this reason, the Flip framework allows to detect those situation and may force the developer to erase explicitely the object to ensure it has control over the life span of the object.</p>

<ul>
<li>if set to <code>flip_ENTITY_USE_RELAXED</code>, the Flip framework will automatically    free any remaining object in the <code>Entity</code></li>
<li>if set to <code>flip_ENTITY_USE_STRICT</code>, the Flip framework will trigger    a <code>flip_FATAL</code> if the <code>Entity</code> is not empty when the underlying Flip type    is removed.    <em>This is the default behavior</em></li>
<li>if set to <code>flip_ENTITY_USE_PEDANTIC</code>, the Flip framework will trigger    a <code>flip_FATAL</code> as in <code>flip_ENTITY_USE_STRICT</code> and will also    ensure that any entity creation or erase only occurs from an observer    notification <code>document_changed</code>.</li>
</ul>

<blockquote><h6>Note</h6> <code>flip_ENTITY_USE</code> is ignored if <code>flip_ENTITY_LOCATION</code> is    set to <code>flip_ENTITY_LOCATION_NONE</code></blockquote>

<p>One will activate one option or another using the processor macros or definitions. For example :</p>

```
flip_ENTITY_USE=flip_ENTITY_USE_RELAXED
```

<h2 id="entityloc"><code>flip_ENTITY_LOCATION</code></h2>

<p>The flip Framework <code>Entity</code> system allows to bind an arbitraty object to a flip <code>Object</code> (or derived) or <code>Type</code>. While being convenient, its memory usage might be a concern if it is only used for object and never for basic types such as <code>Int</code> or <code>Float</code>, or never at all.</p>

<p>For this reason, the Flip framework allows either to have the entity available for any kind of Flip object, to restrict only to flip <code>Object</code> (that is, not any basic types), or to remove completely the feature from Flip.</p>

<ul>
<li>if set to <code>flip_ENTITY_LOCATION_TYPE</code>, the Flip framework will make    the <code>Entity</code> system available for all types.    <em>This is the default behavior</em></li>
<li>if set to <code>flip_ENTITY_LOCATION_OBJECT</code>, the Flip framework will restrict    the use of <code>Entity</code> to flip <code>Object</code> only</li>
<li>if set to <code>flip_ENTITY_LOCATION_NONE</code>, the Flip framework will    remove the <code>Entity</code> feature</li>
</ul>

<blockquote><h6>Note</h6> <code>flip_ENTITY_USE</code> is ignored if <code>flip_ENTITY_LOCATION</code> is    set to <code>flip_ENTITY_LOCATION_NONE</code></blockquote>

<p>One will activate one option or another using the processor macros or definitions. For example :</p>

```
flip_ENTITY_LOCATION=flip_ENTITY_LOCATION_OBJECT
```

<p><sup><a href="dll.md">previous</a> | <a href="msvc.md">next</a></sup></p>

