<p><sup><a href="DataProviderFile.md">previous</a> | <a href="Document.md">next</a></sup></p>

<h1>DataProviderMemory Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/DataProviderMemory.h</code></td></tr>
</table>

```c++
class DataProviderMemory;
```

<p>Generally a data provider represents an abstraction of input serialized data that is platform (endianess and word size) independent.</p>

<p><code>flip::DataProviderMemory</code> is a specialization of data provider which input is memory.</p>

<p>Internally the data is presented in big-endian, and has byte alignment packing.</p>

<p>To input from a file instead of memory, see <a href="../reference/DataProviderFile.md"><code>flip::DataProviderFile</code></a></p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>DataProviderMemory</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>DataProviderMemory</code></td></tr>
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
DataProviderMemory (const std::vector <uint8_t> & data);
```

<p>Constructor. The input of serialization will come from <code>data</code>.</p>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~DataProviderMemory ();
```

<p>Destructor.</p>

<h3 id="member-function-operator >>"><code>operator >></code></h3>
```c++
DataProviderMemory & operator >> (bool & val);
DataProviderMemory & operator >> (char & val);
DataProviderMemory & operator >> (uint8_t & val);
DataProviderMemory & operator >> (int32_t & val);
DataProviderMemory & operator >> (uint32_t & val);
DataProviderMemory & operator >> (int64_t & val);
DataProviderMemory & operator >> (uint64_t & val);
DataProviderMemory & operator >> (double & val);
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

<p><sup><a href="DataProviderFile.md">previous</a> | <a href="Document.md">next</a></sup></p>

