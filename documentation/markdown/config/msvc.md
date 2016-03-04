<p><sup><a href="misc.md">previous</a></sup></p>

<h1>MSVC Warnings Notes</h1>

<p>This chapter gives details on MSVC configuration regarding compiler warnings.</p>

<h2 id="overview">Overview</h2>

<p>To accomodate our customers configurations, we followed a strict policy about warnings. Warnings are always treated as errors, so that flip must compile without generating any warnings.</p>

<p>To provide that, the following MSVS settings are used for the <code>cl</code> compiler :</p>

```
WarningLevel: 4
WarnAsError: true
AdditionalOptions: /Wall
```

<p>We <em>do not</em> advise using this last warning line. In practice, it will activate all possible warnings, and in particular warnings that MSVS turns off by default.</p>

<p>Those additional warnings contain informational warnings, but they will also trigger warnings in the system headers and in particular in the standard library system headers.</p>

<p>As far as MSVS 12.0 is concerned, we decided to silent those warnings at a global scope, rather than silenting them in the source code directly.</p>

<p>The next sections will list all disabled warnings and gives a quick note on the reason and impact on code.</p>

<h2 id="c4251">Warning C4251</h2>

<p><a href="http://msdn.microsoft.com/en-us/library/esew7y1w.aspx">MSDN Warning C4251 Reference</a></p>

```
'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
```

<p>This warning occurs as a false positive when exporting template code.</p>

<p>The regression tests (flip as a dll) ensure that flip is working correctly.</p>

<h2 id="c4265">Warning C4265</h2>

<p><a href="http://msdn.microsoft.com/en-us/library/wzxffy8c.aspx">MSDN Warning C4265 Reference</a></p>

```
'class' : class has virtual functions, but destructor is not virtual
```

<p>While this warning is important, it was disabled because it occurs in standard library headers such as <code><thread></code>, <code><mutex></code> or <code><condition_variable></code>.</p>

<p>We rely on the fact that the clang build will catch those problems.</p>

<h2 id="c4350">Warning C4350</h2>

<p><a href="http://msdn.microsoft.com/en-us/library/0eestyah.aspx">MSDN Warning C4350 Reference</a></p>

```
behavior change: 'member1' called instead of 'member2'
```

<p>This is treated as an informational warning.</p>

<h2 id="c4355">Warning C4355</h2>

<p><a href="http://msdn.microsoft.com/en-us/3c594ae3.aspx">MSDN Warning C4355 Reference</a></p>

```
'this' : used in base member initializer list
```

<p>This is treated as an informational warning. Internally the framework used <code>*this</code> to allow a child object to have access to its parent, when decomposing a big class into smaller feature-orthogonal classes.</p>

<h2 id="c4365">Warning C4365</h2>

<p><a href="http://msdn.microsoft.com/en-us/ms173683.aspx">MSDN Warning C4365 Reference</a></p>

```
'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch
```

<p>While this warning is important, it was disabled because it provides a lot of false positive that the standard permits.</p>

<p>We rely on the fact that the clang build will catch those problems.</p>

<h2 id="c4435">Warning C4435</h2>

<p><a href="http://msdn.microsoft.com/en-us/jj155806.aspx">MSDN Warning C4435 Reference</a></p>

```
'class1' : Object layout under /vd2 will change due to virtual base 'class2'
```

<p>This is treated as an informational warning.</p>

<h2 id="c4514">Warning C4514</h2>

<p><a href="http://msdn.microsoft.com/en-us/cw9x3tcf.aspx">MSDN Warning C4514 Reference</a></p>

```
'function' : unreferenced inline function has been removed
```

<p>This is treated as an informational warning.</p>

<h2 id="c4702">Warning C4702</h2>

<p><a href="http://msdn.microsoft.com/en-us/c26da40e.aspx">MSDN Warning C4702 Reference</a></p>

```
unreachable code
```

<p>This is treated as an informational warning.</p>

<h2 id="c4571">Warning C4571</h2>

<p><a href="http://msdn.microsoft.com/en-us/55s8esw4.aspx">MSDN Warning C4571 Reference</a></p>

```
Informational: catch(...) semantics changed since Visual C++ 7.1;
structured exceptions (SEH) are no longer caught
```

<p>This is treated as an informational warning.</p>

<h2 id="c4640">Warning C4640</h2>

<p><a href="http://msdn.microsoft.com/en-us/4f5c8560.aspx">MSDN Warning C4640 Reference</a></p>

```
'instance' : construction of local static object is not thread-safe
```

<p>The C++11 standard states (section 6.7):</p>

<blockquote><h6>Note</h6> such a variable is initialized the first time control passes through its declaration; such a variable is considered initialized upon the completion of its initialization. [...] If control enters the declaration concurrently while the variable is being initialized, the concurrent execution shall wait for completion of the initialization.</blockquote>

<p>So we ignore this warning. However for compatibility, the cases where this is used are for now marked as non-thread-safe, which is acceptable since this is occured when declaring models.</p>

<h2 id="c4710">Warning C4710</h2>

<p><a href="http://msdn.microsoft.com/en-us/yd3056cz.aspx">MSDN Warning C4710 Reference</a></p>

```
'function' : function not inlined
```

<p>This is treated as an informational warning.</p>

<h2 id="c4820">Warning C4820</h2>

<p><a href="http://msdn.microsoft.com/en-us/t7khkyth.aspx">MSDN Warning C4820 Reference</a></p>

```
'bytes' bytes padding added after construct 'member_name'
```

<p>This is treated as an informational warning.</p>

<p><sup><a href="misc.md">previous</a></sup></p>

