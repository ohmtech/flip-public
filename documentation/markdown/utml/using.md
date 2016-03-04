<p><sup><a href="language.md">previous</a></sup></p>

<h1>Using Utml</h1>

<p>This chapter describes the use of the <code>Utml</code> class.</p>

<h2 id="overview">Overview</h2>

<p>The following describes the <code>Utml</code> static methods.</p>

```
static void       write (DataConsumerBase & consumer, const BackEndIR & backend);
static BackEndIR  read (DataProviderBase & provider, const DataModelBase & model);
```

<p>The first method <code>write</code> can be used to output a generated Utml content from a back-end. It can be used to generate test cases on the fly.</p>

<p>It takes a data consumer on input which might represents a file or a portion of memory.</p>

<p>The second method <code>read</code> is used to read utml content and, with the help of a data model, output a back-end intermediate representation that can then be used to fill a document.</p>

<h2 id="error">Error reporting</h2>

<p>When parsing utml content, if the parser encounters an error, it will fire an exception of type <code>Utml::Error</code>.</p>

<p>When generating utml content, one might <code>trace</code> the error to provide context.</p>

<p>Typically, reading utml will have this general structure :</p>

```
try
{
   backend = Utml::read (provider, model);
}
catch (const Utml::Error & e)
{
   e.trace ();
}
```

<p>Tracing the error will output the error message and its context on the standard output. The following shows typical examples of it :</p>

```
<utml>:1:15: error: Unknown member `something'
flip.Root root{something = 15}
               ^~~~~~~~~
```

```
<utml>:1:20: error: Unexpected value `fals' for Bool type
flip.Root root{bool=fals}
                    ^~~~
```

<p><sup><a href="language.md">previous</a></sup></p>

