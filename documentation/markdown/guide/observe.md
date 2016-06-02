<p><sup><a href="control.md">previous</a> | <a href="signal.md">next</a></sup></p>

<h1>Observing the Model</h1>

<p>Now that we can declare a model and we know how to organize it and manipulate it, this chapter describes how to listen to its changes.</p>

<p>This chapter will use the model declared in the chapter <a href="../guide/observe.md#declare">Declaring the Model</a>.</p>

<h2 id="declare">Declaring and Binding the Observer</h2>

<p>To listen to document modification, one must declare an observer.</p>

<p>All observers must inherit from the template class <code>DocumentObserver</code>, which takes the root class of your model as a template parameter.</p>

<p>To receive document changes, one must register a document observer to the document.</p>

<blockquote><h6>Note</h6> Only one observer can be setup per document, but an observer might dispatch itself to other observers if it wants to.</blockquote>

```c++
class Observer : public flip::DocumentObserver <Song>                         (1)
{
public:
   virtual void document_changed (Song & song) override;                      (2)
}

void  run ()
{
   Observer observer;
   Document document (Model::use (), observer, 123456789ULL, 'OmSt', 'gui '); (3)

   Song & song = document.root <Song> ();

   song.tempo = 120.0;

   document.commit ();                                                        (4)
}
```

<ol>
<li>Make an observer by inheriting from <code>DocumentObserver</code></li>
<li>Override the pure virtual function declared in <code>DocumentObserver</code></li>
<li>Attach the observer to the document</li>
<li>When <code>commit</code> is called, it will fire the <code>document_changed</code> method</li>
</ol>

<h2 id="property">Listening to Property Changes</h2>

<p>When <code>commit</code> is called, it will fire the <code>document_changed</code> method. This method contains the song as a parameter. This song has then the ability to represent the document in its old state as well as new state.</p>

<p>Because of this property, Flip types can know when they have changed. Therefore, listening to tempo change in our example would look like this :</p>

```c++
void  Observer::document_changed (Song & song)
{
   if (song.tempo.changed ())                   (1)
   {
      double new_tempo = song.tempo;            (2)
      double old_tempo = song.tempo.before ();  (3)
   }
}
```

<ol>
<li>Take the branch if the value was changed</li>
<li>Extract the new tempo value</li>
<li>Extract the old tempo value</li>
</ol>

<h2 id="container">Listening to Container Changes</h2>

<p>Listening to container changes works in the same way. The container can know when it has changed. But the container also has the ability to represent both its old and new states.</p>

```c++
void  Observer::document_changed (Song & song)
{
   if (song.tracks.changed ())
   {
      auto it = song.tracks.begin ();
      auto it_end = song.tracks.end ();

      for (; it != it_end ; ++it)
      {
         auto & track = *it;

         if (track.changed ())            (1)
         {
            if (track.added ())          (2)
            {
               ...
            }
            else if (track.resident ())   (3)
            {
               ...
            }
            else if (track.removed ())   (4)
            {
               ...
            }
         }
      }
   }
}
```

<p>The code above will iterate other the list of tracks if it did change.</p>

<ol>
<li>Track life cycle is also detected through the use of <code>changed</code></li>
<li>The track was just added to the container</li>
<li>The track is resident, which means that it was neither added or removed from the container. Since the track itself changed (1), this means that it has inner modification</li>
<li>The track was removed from the container. Its data is still available to the observer, but the model object will be destroyed when <code>document_changed</code> exits.</li>
</ol>

<blockquote><h6>Note</h6> Traversing a <code>Collection</code> for changes is exactly similar to traversing an <code>Array</code>.</blockquote>

<p>In the code above, a <code>Track</code> will be reported as changed when the <code>Track</code> changed itself, or one of its children, for example one <code>Clip</code> <code>position</code></p>

<blockquote><h6>Important</h6> When an object is <code>changed</code> this means that subtree it represents have changed, maybe somewhere deep in the tree.</blockquote>

<h2 id="splice">Listening to Container Elements Move</h2>

<p>Containers like <code>Array</code> or <code>Collection</code> have a <code>splice</code> operation which allows to move elements from one container or in the same container for <code>Array</code>.</p>

<p>If <code>splice</code> is used, then the document needs to be observed in a slightly different way, to be able to detect moves in the hierarchy.</p>

<p>An element moved is neither <code>added</code> or <code>removed</code> so it is resident. However the iterator that wrap the object can be also <code>added</code> or <code>removed</code>. When no splice operation is called, the iterator state is always the same as the element it wraps.</p>

<p>Then when an element is moving, the difference between the iterator state and the element state allows to observe moves, as shown in the example below.</p>

```c++
void  Observer::document_changed (Song & song)
{
   if (song.tracks.changed ())
   {
      auto it = song.tracks.begin ();
      auto it_end = song.tracks.end ();

      for (; it != it_end ; ++it)
      {
         auto & track = *it;

         if (it.removed () && track.resident ())
         {
            // The track is moving from this position...
         }

         if (it.added () && track.resident ())
         {
            // ... to this position
         }
      }
   }
}
```

<p>The next chapter, <a href="../guide/signal.md">Signalling the Model</a> will show how to send non-persistent messages to objects of the model.</p>

<p><sup><a href="control.md">previous</a> | <a href="signal.md">next</a></sup></p>

