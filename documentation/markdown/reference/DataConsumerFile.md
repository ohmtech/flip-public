<p><sup><a href="collection_iterator.md">previous</a> | <a href="DataConsumerMemory.md">next</a></sup></p>

<h1>DataConsumerFile Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/contrib/DataConsumerFile.h</code></td></tr>
</table>

```c++
class DataConsumerFile;
```

<blockquote><h6>Note</h6> Classes part of <code>contrib/</code> are not supported on every platform.    This class is not supported on the WinRT platform.</blockquote>

<p>Generally a data consumer represents an abstraction of output serialized data that is platform (endianess and word size) independent.</p>

<p><code>flip::DataConsumerFile</code> is a specialization of data consumer which output is a file.</p>

<p>Internally the data is presented in big-endian, and has byte alignment packing.</p>

<p>To output to memory instead of a file, see <a href="../reference/DataConsumerMemory.md"><code>flip::DataConsumerMemory</code></a></p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>DataConsumerFile</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>DataConsumerFile</code></td></tr>
<tr><td><code><a href="#member-function-operator <<">operator <<</a></code></td><td>Inserts value in the consumer</td></tr>
<tr><td><code><a href="#member-function-push">push</a></code></td><td>Inserts raw data in the consumer</td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
DataConsumerFile (const char * path_0);
```

<p>Constructor. The output of serialization will be done to the file with path the null terminated string <code>path_0</code>.</p>

<blockquote><h6>Important</h6> The encoding of <code>path_0</code> is <code>UTF-8</code></blockquote>

<p>The path should make possible to open a file for writing. If any error occurs, the constructor will throw <code>std::runtime_error</code>.</p>

<h3 id="member-function-destructor">Destructor</h3>
```c++
~DataConsumerFile ();
```

<p>Destructor.</p>

<h3 id="member-function-operator <<"><code>operator <<</code></h3>
```c++
DataConsumerFile & operator << (bool val);                (1)
DataConsumerFile & operator << (char val);                (1)
DataConsumerFile & operator << (uint8_t val);             (1)
DataConsumerFile & operator << (int32_t val);             (1)
DataConsumerFile & operator << (uint32_t val);            (1)
DataConsumerFile & operator << (int64_t val);             (1)
DataConsumerFile & operator << (uint64_t val);            (1)
DataConsumerFile & operator << (double val);              (1)
DataConsumerFile & operator << (const char * val_0);      (2)
DataConsumerFile & operator << (const std::string & val); (3)
```

<p>Inserts value into the consumer.</p>

<ol>
<li>Inserts value into the consumer and perform automatic byte swapping and packing.</li>
<li>Inserts the null terminated string into the consumer.</li>
<li>Inserts the string into the consumer.</li>
</ol>

<blockquote><h6>Important</h6> String insertions do not contain the dynamic string size.</blockquote>

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

<h3 id="member-function-push"><code>push</code></h3>
```c++
void  push (const uint8_t * data_ptr, size_t data_size)
```

<p>Inserts raw data into the consumer. No byte swap is performed and the packing of data is not changed.</p>

<blockquote><h6>Important</h6> The insertion does not include the data size.</blockquote>

<p><sup><a href="collection_iterator.md">previous</a> | <a href="DataConsumerMemory.md">next</a></sup></p>

