<p><sup><a href="misc.md">previous</a></sup></p>

<h1>Model Versioning</h1>

<p>Over time, your model will change, and so its revision. Document then needs to be converted, and this chapter describes how to do so.</p>

<h2 id="converters">Converters</h2>

<p>Your <code>model</code> folder should contain a <code>conv</code> folder. It will contains all your format version changes in a single place. Since Flip format conversion system is rather flexible, it is very easy to make document format changes, so you are very likely to make a lot of them.</p>

<p>You should name your conversion classes <code>Converter#1_#2</code> where <code>#1</code> would be the initial revision, according to your version source control naming. In the same fashion, <code>#2</code> would be your destination revision.</p>

<h2 id="dispatch">Conversion graph</h2>

<p>Just after reading a serialized document in <code>BackEndMl</code> or <code>BackEndBinary</code> to the <code>BackEndIR</code> format, you need to convert the latter format to the revision of the model currently used in your application.</p>

<p><code>BackEndMl</code> or <code>BackEndBinary</code> are model revision agnostic, and so is <code>BackEndIR</code>, so that you don't need to maintain all versions of the model to be able to convert.</p>

<p>The general idea is to convert from one conversion to another the <code>BackEndIR</code> format until you've matched the revision available to use with your application.</p>

<p>Typically, this global conversion process looks like this :</p>

```c++
DataProviderFile provider ("/path/to/file");

// tell the backend to automatically recognize the binary format
BackEndIR backend;
backend.register_backend <BackEndBinary> ();

bool ok_flag = backend.read (provider);
if (!ok_flag) return;   // a corruption occured

// now starts the conversion process, where every converters process
// the 'backend' in-place, and changes its version

if (backend.version == "myapp.beta.1")
{
   Converter_beta1_beta2 converter;
   converter.process (backend);

   // now backend.version == "myapp.beta.2"
}

if (backend.version == "myapp.beta.3")
{
   // beta.3 was a mistake, so we decide to rollback it to beta.2
   // for our loyal beta testers
   Converter_beta3_beta2 converter;
   converter.process (backend);

   // now backend.version == "myapp.beta.2"
}

if (backend.version == "myapp.beta.2")
{
   Converter_beta2_r100 converter;
   converter.process (backend);

   // now backend.version == "myapp.r100"
   // which is the current model revision
}

Document document (Model::use (), user_id, manufacturer_id, component_id);

// change the document with the content of the backend
document.read (backend);

// commit the changes
document.commit ();
```

<h2 id="converter">Converter</h2>

<blockquote><h6>Note</h6> For now the conversion process is done entirely manually, and require deep    knowledge of the internals of Flip. It will be soon simplified by using    dedicated tool classes.</blockquote>

<p>Now that we have seen the global conversion graph managment, let's look at a single converter anatomy.</p>

<p><code>BackEndIR</code> contains a member <code>version</code> string which is the current revision of the model. A part from that, it contains a member <code>root</code> which is the starting point of every conversions.</p>

<p><code>root</code> itself is a <code>BackEndIR::Type</code> which is a generic way to represent a <code>Type</code> in the document. It can represent either an <code>Object</code>, but also a container type or a basic type like <code>Float</code>.</p>

<p><code>Type</code> contains a <code>type_name</code> as well as a <code>type_id</code> to allows to know which kind of type we are manipulating.</p>

<ul>
<li>If the <code>Type</code> is an object, then <code>Type::members</code> is the list of the members of the object</li>
<li>If the <code>Type</code> is an array, then <code>Type::array</code> is the list of the element of the array</li>
<li>If the <code>Type</code> is a collection, then <code>Type::collection</code> is the list of the element of the collection</li>
<li>If the <code>Type</code> is a value type like <code>Float</code>, then <code>Type::value</code> is the value</li>
</ul>

<p>For example let's say that we had the following model :</p>

```c++
class Note : public Object
{
public:
   String title;
   String body;
};

class Root : public Object
{
public:
   Collection <Note> notes;
};
```

<p>And that we want to convert to this new model, where we added a member <code>date</code></p>

```c++
class Note : public Object
{
public:
   String title;
   String body;
   String date;
};

class Root : public Object
{
public:
   Collection <Note> notes;
};
```

<p>Then the converter will need to add a member and initialize it to a value this way :</p>

```c++
void  Converter::process (BackEndIR backend)
{
   std::string current_date = today ();

   for (auto & element : backend.root.collection)
   {
      auto & note = element.second;

      auto & date = *note.members.emplace_back (std::make_pair ("date", Type ()));

      date.type_name = "flip.Blob"; // String is a Blob
      date.type_id = TypeId::BLOB;
      date.value.blob.assign (current_date.begin (), current_date.end ());
      date.value.blob_string_flag = true;
   }
}
```

<p><sup><a href="misc.md">previous</a></sup></p>

