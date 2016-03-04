<p><sup><a href="gyp.md">previous</a> | <a href="dll.md">next</a></sup></p>

<h1>Setting up Manually</h1>

<p>This chapter explains how to set up your build environment manually.</p>

<h2 id="overview">Overview</h2>

<p>Integrating the Flip framework consists of :</p>

<ul>
<li>adding the needed source and optionally header files to your build environment</li>
<li>set up the include path</li>
<li>set up necessary IDE options</li>
</ul>

<p>Even when not using the <code>gyp</code> build system, the <code>gyp</code> and <code>gypi</code> makes a good reference for the necessary tasks to execute to integrate the Flip framework.</p>

<p>The following sections will describe each of those tasks.</p>

<h2 id="files">Including Source and Header Files</h2>

```
include/
   flip/
      contrib/
      detail/
src/
   contrib/
   detail/
```

<p>The only necessary files to include are the <code>.cpp</code> source files contained directly in <code>src</code> and <code>src/detail</code> folders. This represents the core of the Flip framework. In particular the core does not depend on the <code>contrib</code> sources.</p>

<p>You can optionnaly include the header <code>.h</code> and code header <code>.hpp</code> files.</p>

<blockquote><h6>Important</h6> If including those files to your build system generate errors for XCode, please make sure to read the <a href="../config/manual.md#headermap">Troubleshooting XCode header inclusion</a> below</blockquote>

<h2 id="include">Setting up the include path</h2>

<p>The only path to include in your project IDE is the <code>include</code> folder.</p>

<h2 id="include">Setting up IDE options</h2>

<p>If you are including header files, you will want to troubleshoot XCode header inclusion as described in the next section.</p>

<p>The Flip framework natively both support the <code>C++11</code> and <code>C++14</code> language dialect.</p>

<p>On Windows you need to add a dependency on the <code>ws2_32.lib</code> Winsocket 2 library. You also need to disable the following warnings :</p>

<ul>
<li><a href="http://msdn.microsoft.com/en-us/library/esew7y1w.aspx">Warning C4251</a></li>
</ul>

<p>If you enabled more warnings through the <code>AdditionalOptions: /Wall</code> directive, then please read <a href="../config/msvc.md">MSVC Warnings Notes</a></p>

<h2 id="headermap">Troubleshooting XCode header inclusion</h2>

<p>The default XCode header inclusion rule specifies that headers added to the project will be searched directly. This means that the <code>Document.h</code> file could be accessed as :</p>

```c++
#include "Document.h"
```

<p>instead of :</p>

```c++
#include "flip/Document.h"
```

<p>This is problematic on platforms where the HFS filesystem is specified as case insensitive. In this case system header files including for example <code>float.h</code> will use <code>flip/Float.h</code> instead.</p>

<p>On MacOS X, the issue arrises for <code>flip/Float.h</code> and <code>flip/Signal.h</code>.</p>

<p>To overcome this problem, the Flip user developer will have to explicitely tell XCode not to search those files by specifying <code>USE_HEADERMAP</code> to <code>NO</code>. This is done my adding a User-Defined Setting either in your Project or Target Build Settings.</p>

<p>More information on this matter is available <a href="http://www.cocoabuilder.com/archive/xcode/285003-xcode-picks-up-headers-from-the-wrong-location.html">here</a>.</p>

<p><sup><a href="gyp.md">previous</a> | <a href="dll.md">next</a></sup></p>

