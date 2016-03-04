<p><sup><a href="files.md">previous</a> | <a href="manual.md">next</a></sup></p>

<h1>Setting up Using <code>gyp</code></h1>

<p>This chapter explains how to set up your build environment using the <code>gyp</code> tool.</p>

<h2 id="overview">Overview</h2>

<p><code>gyp</code>, "Generate your project" is a tool made by Google which was made for the Chromium project their Google Chrome application. The tool allows to have a set of files in editable text format that can be used to generate automatically Windows Visual Studio or Apple XCode project.</p>

<p>This tool is used by the Flip framework in two ways :</p>

<ul>
<li>To provide a convenient way to make IDE projects for automatic testing</li>
<li>To allow Flip user developer to quickly setup all needed files to    integrate the Flip framework into their build environment</li>
</ul>

<p><code>gyp</code> requires a proper installation of the <code>python</code> programming language to work.</p>

<p>The <code>gyp</code> system documentation is outside of the scope of this guide. More information on the <code>gyp</code> tool is available <a href="http://chromium.googlesource.com/external/gyp/+/master/docs/UserDocumentation.md">here</a>.</p>

```
configure.py
flip.gyp
flip_lib.gpyi
flip_src.gpyi
src/
   src.gpyi
test/
   test.gypi
   win.gypi
   xcode.gypi
```

<p>The following section will describe the purpose of every <code>gyp</code> and <code>gypi</code> file.</p>

<h2 id="top">Top Level Files</h2>

<h3 id="top-configure"><code>configure.py</code></h3>

<p>While not a <code>gyp</code> file, <code>configure.py</code> is a <code>python</code> file used to produce projects for regression and performance testing. It requires an installation of <code>python</code> 2.7 or greater.</p>

<p>Executing this <code>python</code> script will create a <code>projects</code> folder at the top level and will put all required files to build and run tests.</p>

<h3 id="top-flip.gyp"><code>flip.gyp</code></h3>

<p><code>flip.gyp</code> is a top level <code>gyp</code> file that produces all the test targets to test the Flip framework.</p>

<h3 id="top-flip_lib.gypi"><code>flip_lib.gypi</code></h3>

<p><code>flip_lib.gypi</code> is a top level <code>gypi</code> file. When integrating the Flip framework to your build system, this is typically the only file to include.</p>

<p>It will add all source and header files to integrate the Flip framework core and contribution files. It will also set up the include path and makes sure that every dependent target have their include path correctly setup.</p>

<blockquote><h6>Important</h6> If including this file to your build system generate errors for XCode, please make sure to read the <a href="../config/gyp.md#headermap">Troubleshooting XCode header inclusion</a></blockquote>

<h3 id="top-flip_src.gypi"><code>flip_src.gypi</code></h3>

<p><code>flip_src.gypi</code> is a top level <code>gypi</code> file. In contains only all source and header files and set up include path accordingly.</p>

<blockquote><h6>Important</h6> If including this file to your build system generate errors for XCode, please make sure to read the <a href="../config/gyp.md#headermap">Troubleshooting XCode header inclusion</a></blockquote>

<h2 id="src"><code>src</code> Files</h2>

<h3 id="src-src.gypi"><code>src.gypi</code></h3>

<p><code>src/src.gypi</code> contains only the source and header files of the Flip framework core and contribution.</p>

<blockquote><h6>Important</h6> If including this file to your build system generate errors for XCode, please make sure to read the <a href="../config/gyp.md#headermap">Troubleshooting XCode header inclusion</a></blockquote>

<h2 id="test"><code>test</code> Files</h2>

<p>The <code>gypi</code> files in test are only used for regression and performance tests. They are typically not included in your build environment. However they provide a reference for specific configuration, for example to set up dynamic library linkage.</p>

<h3 id="test-test.gypi"><code>test.gypi</code></h3>

<p><code>test.gypi</code> contains all targets to produce all tests.</p>

<h3 id="test-win.gypi"><code>win.gypi</code></h3>

<p><code>win.gypi</code> contains all specific Windows Visual Studio project options. It provides debug and release as well as 32-bit and 64-bit configurations.</p>

<p>It provides the only dependency of Flip, which is Winsockets 2 <code>ws2_32.lib</code>.</p>

<p>Finally it contains the set of disabled warnings necessary for the Flip framework to compile without any kind of warning :</p>

<ul>
<li><a href="http://msdn.microsoft.com/en-us/library/esew7y1w.aspx">Warning C4251</a></li>
</ul>

<h3 id="test-xcode.gypi"><code>xcode.gypi</code></h3>

<p><code>xcode.gypi</code> contains all specific Apple XCode project options. It provides debug and release as well as 32-bit and 64-bit configurations.</p>

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

<p>To overcome this problem, the Flip user developer will have to explicitely tell XCode not to search those files by specifying <code>USE_HEADERMAP</code> to <code>NO</code>.</p>

<p>More information on this matter is available <a href="http://www.cocoabuilder.com/archive/xcode/285003-xcode-picks-up-headers-from-the-wrong-location.html">here</a>.</p>

<p>An example of this setting can be find in the top level <code>flip.gyp</code> file :</p>

```c++
'xcode_settings': {
   'USE_HEADERMAP': 'NO',
},
```

<p><sup><a href="files.md">previous</a> | <a href="manual.md">next</a></sup></p>

