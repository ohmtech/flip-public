<p><sup><a href="declare.md">previous</a> | <a href="control.md">next</a></sup></p>

<h1>Organizing your Code</h1>

<p>Now that you know how to declare a model, but before we go further into Flip code, now is the time to expose strategies to organize your code to use Flip.</p>

<p>Ohm Force has been using its Flip framework for years, to make, among other internal programs, its Ohm Studio application.</p>

<p>Over the years, we have developed a robust workflow to work with Flip. This chapter describes how you should organize your code in the first place, to avoid big refactors or headaches at a late stage of development.</p>

<h2 id="layout">Code Layout</h2>

<p>You should separate the model, client and server code in 3 separate folders, and 3 separate namespaces.</p>

<p>Typically you should create a folder named <code>model</code> in which all classes are in the namespace <code>model</code> . The model is going to be used in both the client code and the server code. Since the server code is generally going to be running on linux, you want to avoid avoid dependencies between your model and code that wouldn’t compile on linux, and would be unnecessary for the server.</p>

<p>Typically your folder client and server and their associated namespaces will have a dependency on model .</p>

```
your_company/
   your_product/
      model/
         ... model classes ...
      client/
         ... client classes ...
      server/
         ... server classes ...
```

<h2 id="converters">Converters</h2>

<p>Your <code>model</code> folder should contain a <code>conv</code> folder. It will contains all your format version changes in a single place. Since Flip format conversion system is rather flexible, it is very easy to make document format changes, so you are very likely to make a lot of them.</p>

<p>To avoid polluting the model folder, having it separated in a different folder is a good solution.</p>

<p>You should name your conversion classes <code>Converter#1_#2</code> where <code>#1</code> would be the initial revision, according to your version source control naming. In the same fashion, <code>#2</code> would be your destination revision.</p>

<p>If you are working with many people on a Flip project, many people might modify the model simulatenously. This is not an issue when developping, as the server is bundled in the client, and because you can generally start on a fresh document to test your changes.</p>

<p>However when your application is running in a production environment, conversion will be need to be done, somehow like migrating a database. The model changes are therefore scattered over all the Flip classes which might be not easy when trying to gather all the changes to write a converter.</p>

<p>Therefore you should maintain a <code>Converter.txt</code> text file, typically in your conv where you will sum up all the changes needed for the next conversion, and maybe some directions on how to convert the document.</p>

<p>This process is covered in more details in the chapter <a href="../guide/conversion.md">Model Versioning</a>.</p>

<h2 id="class">Classes Naming Conventions</h2>

<p>You should name your classes like <code>your_company.your_product.ClassName</code> where ClassName would be the name of your class.</p>

<p>For example a typical class name would be <code>ohm.studio.Root</code>. It is defined when declaring the class as for example in the following code :</p>

```c++
Model::declare <Root> ()
   .name ("ohm.studio.Root")
```

<h2 id="enum">Enums Naming Conventions</h2>

<p>You should name your classes like <code>your_company.your_product.ClassName.EnumName</code> where ClassName would be the name of your class.</p>

<p>For example a typical class name would be <code>ohm.studio.ViewMetrics.Lod</code>. It is defined when declaring the class as for example in the following code :</p>

```c++
Model::declare <Lod> ()
   .name ("ohm.studio.ViewMetrics.Lod")
```

<h2 id="declaration">Declaration Conventions</h2>

<p>Finally your <code>model</code> should contain a function that will at least handle the declaration of the model. Each Flip class should have a <code>static</code> function member called <code>declare</code>. Typically it would look like :</p>

```c++
void  declare ()
{
   ObjectRef::declare ();
   Selection::declare ();


   ... code skipped ...


   Root::declare ();
}
```

<p>The dependency system makes it easier to declare all the classes in the right order in a single function when a project becomes complex.</p>

<p>The next chapter, <a href="../guide/control.md">Controlling the Model</a> will guide you through the task of controlling the model.</p>

<p><sup><a href="declare.md">previous</a> | <a href="control.md">next</a></sup></p>

