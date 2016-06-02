<p><sup><a href="DataModel.md">previous</a> | <a href="DataProviderMemory.md">next</a></sup></p>

<h1>DataProviderFile Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/contrib/DataProviderFile.h</code></td></tr>
</table>

```c++
class DataProviderFile;
```

<blockquote><h6>Note</h6> Classes part of <code>contrib/</code> are not supported on every platform.    This class is not supported on the WinRT platform.</blockquote>

<p>Generally a data provider represents an abstraction of input serialized data that is platform (endianess and word size) independent.</p>

<p><code>flip::DataProviderFile</code> is a specialization of data provider which input is a file.</p>

<p>Internally the data is presented in big-endian, and has byte alignment packing.</p>

<p>To input from memory instead of a file, see <a href="../reference/DataProviderMemory.md"><code>flip::DataProviderMemory</code></a></p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>DataProviderFile</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>DataProviderFile</code></td></tr>
<tr><td><code><a href="#member-function-operator >>">operator >></a></code></td><td>Extracts value from the provider</td></tr>
<tr><td><code><a href="#member-function-read_string">read_string</a></code></td><td>Extracts string from the provider</td></tr>
<tr><td><code><a href="#member-function-pull">pull</a></code></td><td>Extracts raw data from the provider</td></tr>
<tr><td><code><a href="#member-function-pull">pull</a></code></td><td>Returns the current reading position in the stream</td></tr>
<tr><td><code><a href="#member-function-seek_start">seek_start</a></code></td><td>Seek reading position relative to the beginning of the stream</td></tr>
<tr><td><code><a href="#member-function-seek_relative">seek_relative</a></code></td><td>Seek reading position relative to the current position in the stream</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
DataProviderFile (const char * path_0);
```

<p>Constructor. The input of serialization will come from the file with path the null terminated string <code>path_0</code>.</p>

<blockquote><h6>Important</h6> The encoding of <code>path_0</code> is <code>UTF-8</code></blockquote>

<p>The path should make possible to open a file for reading. If any error occurs, the constructor will throw <code>std::runtime_error</code>.</p>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~DataProviderFile ();
```

<p>Destructor.</p>

<h3 id="member-function-operator >>"><code>operator >></code></h3>
```c++
DataProviderFile & operator >> (bool & val);
DataProviderFile & operator >> (char & val);
DataProviderFile & operator >> (uint8_t & val);
DataProviderFile & operator >> (int32_t & val);
DataProviderFile & operator >> (uint32_t & val);
DataProviderFile & operator >> (int64_t & val);
DataProviderFile & operator >> (uint64_t & val);
DataProviderFile & operator >> (double & val);
```

<p>Extracts value from the provider.</p>

<p>If any error occurs (such as reading past the end of the stream), the method will throw <code>std::runtime_error</code>.</p>

<p>Example :</p>

```c++
std::vector <uint8_t> data;
DataConsumerMemory consumer (data);

std::string str ("Flip");

consumer << true;
consumer << int32_t (2);
consumer << 2.5;

consumer << uint64_t (str.size ());
consumer << str;

DataProviderMemory provider (data);
bool val_b;
int32_t val_i;
double val_d;
std::string val_s;

consumer >> val_b; // true
consumer >> val_i; // 2
consumer >> val_d; // 2.5

uint64_t str_size;
consumer >> str_size;
val_s = consumer.read_string (str_size);   // "Flip"

char val_c;
consumer >> val_c; // throws std::runtime_error
```

<h3 id="member-function-read_string"><code>read_string</code></h3>
```c++
std::string read_string (size_t size);
```

<p>Extracts string from the provider.</p>

<p>If any error occurs (such as reading past the end of the stream), the method will throw <code>std::runtime_error</code>.</p>

<h3 id="member-function-pull"><code>pull</code></h3>
```c++
const uint8_t *   pull (size_t data_size);
```

<p>Extracts <code>data_size</code> bytes of raw data from the provider. No byte swap is performed and the packing of data is not changed.</p>

<p>If any error occurs (such as reading past the end of the stream), the method will throw <code>std::runtime_error</code>.</p>

<h3 id="member-function-pull"><code>pull</code></h3>
```c++
size_t tell ();
```

<p>Returns the current reading position in the stream.</p>

<p>If any error occurs (such as reading past the end of the stream), the method will throw <code>std::runtime_error</code>.</p>

<h3 id="member-function-seek_start"><code>seek_start</code></h3>
```c++
seek_start (size_t offset_abs = 0);
```

<p>Seek reading position to <code>offset_abs</code>, relative to the beginning of the stream.</p>

<p>If any error occurs (such as reading past the end of the stream), the method will throw <code>std::runtime_error</code>.</p>

<h3 id="member-function-seek_relative"><code>seek_relative</code></h3>
```c++
seek_start (size_t offset_rel = 0);
```

<p>Seek reading position to <code>offset_rel</code>, relative to the current position in the stream.</p>

<p>If any error occurs (such as reading past the end of the stream), the method will throw <code>std::runtime_error</code>.</p>

<p><sup><a href="DataModel.md">previous</a> | <a href="DataProviderMemory.md">next</a></sup></p>

