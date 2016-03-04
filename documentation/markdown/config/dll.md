<p><sup><a href="manual.md">previous</a> | <a href="misc.md">next</a></sup></p>

<h1>Using Flip as a Dynamic Linked Library (DLL)</h1>

<p>This chapter explains how to set up your build environment to use the Flip framework in a Dynamic Linked Library (dll).</p>

<h2 id="overview">Overview</h2>

<p>Integrating the Flip framework as a Dynamic Linked Library consists on exporting, importing or changing the visibility of symbols. Those changes are platform specific.</p>

<p>Even when not using the <code>gyp</code> build system, the <code>gyp</code> and <code>gypi</code> makes a good reference for the necessary tasks to execute to integrate the Flip framework.</p>

<p>The following sections will describe tasks to achieve.</p>

<h2 id="gyp">Using the <code>gyp</code> build system</h2>

<p>This section describes how to use the Flip framework as a Dynamic Linked Library when using the <code>gyp</code> build system.</p>

<p>It consists of two parts :</p>

<ul>
<li>Setting up the options in the DLL target</li>
<li>Setting up the options in the target using the DLL target</li>
</ul>

<p>The following two subsections will describe those two tasks.</p>

<h3 id="gyp-dll">In the DLL target</h3>

<p>From the DLL target point of view, one will need to :</p>

<ul>
<li>Set the type of the target to <code>shared_library</code></li>
<li>Enable the type registry</li>
<li>On XCode, put the visibility of symbol to <code>default</code></li>
<li>On Visual Studio, set the decl specifications to <code>dllexport</code></li>
</ul>

<p>The following block of code shows how this is done in a <code>gypi</code> file.</p>

```
{
   'target_name': 'my_dll_target',
   'type': 'shared_library',

   'xcode_settings': {
      'OTHER_CFLAGS': [
         '-fvisibility=default',
      ],
   },

   'defines': [
      'flip_TYPE_REGISTRY_MODE=flip_TYPE_REGISTRY_ENABLED',
   ],

   'conditions': [
      ['OS=="win"', {
         'defines': [
            'flip_API=__declspec(dllexport)',
            'flip_API_EXPORT=__declspec(dllexport)',
         ],
      }],
   ],

   'includes' : [
      'relative/path/to/flip_src.gypi',
   ],
}
```

<h3 id="gyp-main">In the target using the DLL target</h3>

<p>From the target using the DLL target point of view, one will need to :</p>

<ul>
<li>Enable the type registry</li>
<li>On XCode, put the visibility of symbol to <code>default</code></li>
<li>On Visual Studio, set the decl specifications to    <code>dllimport</code> or <code>dllexport</code> accordingly</li>
</ul>

<p>The following block of code shows how this is done in a <code>gypi</code> file.</p>

```
{
   'target_name': 'my_main_target',

   'xcode_settings': {
      'OTHER_CFLAGS': [
         '-fvisibility=default',
      ],
   },

   'dependencies': [
      'my_dll_target',
   ],

   'defines': [
      'flip_TYPE_REGISTRY_MODE=flip_TYPE_REGISTRY_ENABLED',
   ],

   'conditions': [
      ['OS=="win"', {
         'defines': [
            'flip_API=__declspec(dllimport)',
            'flip_API_EXPORT=__declspec(dllexport)',
         ],
      }],
   ],

   'include_dirs': [
      'relative/path/to/include',
   ],

   ...your sources and everything else...
}
```

<h2 id="manual">Doing it Manually</h2>

<p>This section describes how to integrate the Flip framework as a Dynamic Linked Library manually in your build system.</p>

<p>It consists of two parts :</p>

<ul>
<li>Setting up the options in the DLL target</li>
<li>Setting up the options in the target using the DLL target</li>
</ul>

<p>The following two subsections will describe those two tasks for each platform.</p>

<h3 id="manual-xcode">XCode DLL Target</h3>

<p>On XCode, one will need to set up a dynamic linked library like a bundle.</p>

<p>All Flip framework core and optionnaly contribution files must be added to the target.</p>

<p>The XCode setting "Other C Flags" (<code>OTHER_CFLAGS</code>) should add the line <code>-fvisibility=default</code></p>

<p>The XCode setting "Preprocessor Macros" (<code>GCC_PREPROCESSOR_DEFINITIONS</code>) should add the line <code>flip_TYPE_REGISTRY_MODE=flip_TYPE_REGISTRY_ENABLED</code></p>

<h3 id="manual-visual">Visual Studio DLL Target</h3>

<p>On Visual Studio, one will need to set up a dynamic linked library.</p>

<p>All Flip framework core and optionnaly contribution files must be added to the target.</p>

<p>The Visual Studio Configuration Properties for C/C++ for Preprocessor should add to the Preprocessor Definitions the following element :</p>

<ul>
<li><code>flip_TYPE_REGISTRY_MODE=flip_TYPE_REGISTRY_ENABLED</code></li>
<li><code>flip_API=__declspec(dllexport)</code></li>
<li><code>flip_API_EXPORT=__declspec(dllexport)</code></li>
</ul>

<h3 id="manual-xcode2">XCode using the DLL Target</h3>

<p>The XCode setting "Other C Flags" (<code>OTHER_CFLAGS</code>) should add the line <code>-fvisibility=default</code></p>

<p>The XCode setting "Preprocessor Macros" (<code>GCC_PREPROCESSOR_DEFINITIONS</code>) should add the line <code>flip_TYPE_REGISTRY_MODE=flip_TYPE_REGISTRY_ENABLED</code></p>

<h3 id="manual-visual2">Visual Studio using the DLL Target</h3>

<p>The Visual Studio Configuration Properties for C/C++ for Preprocessor should add to the Preprocessor Definitions the following element :</p>

<ul>
<li><code>flip_TYPE_REGISTRY_MODE=flip_TYPE_REGISTRY_ENABLED</code></li>
<li><code>flip_API=__declspec(dllimport)</code></li>
<li><code>flip_API_EXPORT=__declspec(dllexport)</code></li>
</ul>

<blockquote><h6>Note</h6> the declspec for flip_API_EXPORT must be dllexport and not dllimport.</blockquote>

<p><sup><a href="manual.md">previous</a> | <a href="misc.md">next</a></sup></p>

