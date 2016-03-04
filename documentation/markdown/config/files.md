<p><sup><a href="about.md">previous</a> | <a href="gyp.md">next</a></sup></p>

<h1>Files Hierarchy</h1>

<p>This chapter describes the files hierarchy or structure of the Flip framework.</p>

<h2 id="overview">Overview</h2>

<p>This section gives the overview of the structure of the Flip framework. The following sections will then describe in more details each element of that structure.</p>

<p>The Flip framework as the following structure. This structure only shows relevant informations for setting up the build environment. For example the documentation file structure is hidden for clarity.</p>

```
include/
   flip/
      contrib/
      detail/
projects/
src/
   contrib/
   detail/
test/
   debug/
   fuzz/
   perf/
   regress/
```

<ul>
<li>the <code>include</code> folder contains only Flip framework headers and code headers files</li>
<li>the optional <code>projects</code> folder is created when using the <code>gyp</code> tool</li>
<li>the <code>src</code> folder contains only Flip framework source files</li>
<li>the <code>test</code> folder contains source and header files used to test the Flip framework</li>
</ul>

<p>The following sections will describe in more details each element of the structure above.</p>

<h2 id="include">The <code>include</code> folder</h2>

```
include/
   flip/
      contrib/
      detail/
```

<p>The <code>include</code> folder contains only Flip framework headers and code headers files.</p>

<p>Typically developers will make the <code>include</code> path available in their header paths so that the header file <code>Document</code> can be reached using <code></code> for example.</p>

<p>The top level <code>flip</code> files contains every public header files which represent the core of the Flip framework. Flip user developers will typically use those files to work with Flip.</p>

<p>The <code>contrib</code> files contains public header files that can be optionally used to work Flip. They do not belong to the core itself, and generally represents specific platform features. For example the <code>DataConsumerFile</code> sits in this directory, whereas the <code>DataConsumerMemory</code> belongs to the Flip framework core.</p>

<p>The <code>detail</code> files contains private header files used by the Flip framework core. Flip user developers should never include those files.</p>

<h2 id="src">The <code>src</code> folder</h2>

```
src/
   contrib/
   detail/
```

<p>The <code>src</code> folder contains only Flip framework source files.</p>

<p>The top level <code>flip</code> files contains every source files implementing the core of the Flip framework.</p>

<p>The <code>contrib</code> files contains source files that can be optionally used to work Flip. They do not belong to the core itself, and generally represents specific platform features. The flip top level files do not depend on the <code>contrib</code> files so that those files don't necesseraly need to be compiled with Flip.</p>

<p>The <code>detail</code> files contains private source files used by the Flip framework core.</p>

<h2 id="projects">The <code>projects</code> folder</h2>

```
projects/
```

<p>When using the <code>gyp</code> tool, the <code>projects</code> folder will contain the generated project or make files to run regression and performance tests.</p>

<p>Typically, when used on Windows, the <code>projects</code> folder will contain the Visual Studio solution as well as all necesserary project files to build tests.</p>

<p>When used on MacOS X, the <code>projects</code> folder will contain the XCode project necesserary to build tests.</p>

<h2 id="test">The <code>test</code> folder</h2>

```
test/
   debug/
   fuzz/
   perf/
   regress/
```

<p>The <code>test</code> folder contains all source and header files needed to build and run regression and performance tests of the Flip framework.</p>

<p>The <code>debug</code> folder contains some files used to help the Flip framework developer to debug the internals of the Flip framework core.</p>

<p>The <code>fuzz</code> folder contains fuzzing tests implementation to provide automatic bug finding in the Ffip framework core.</p>

<p>The <code>perf</code> folder contains source and header files used to measure the performance of the Flip framework and to track performance regressions.</p>

<p>The <code>regress</code> folder contains source and header files used to detect regressions in the Flip framework.</p>

<p><sup><a href="about.md">previous</a> | <a href="gyp.md">next</a></sup></p>

