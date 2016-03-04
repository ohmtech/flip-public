<p><sup><a href="observe.md">previous</a> | <a href="misc.md">next</a></sup></p>

<h1>Working with a Remote Server</h1>

<p>At this point, you are able to declare a model and interact with it by controlling it and observing it. But still this happens only on a local computer.</p>

<p>This chapter exposes how Flip works with a remote server and brings collaboration features to your application.</p>

<h2 id="workflow">Commit/Push/Pull Model</h2>

<p>When you call <code>commit</code> on a document, Flip will create the transaction that represents the change between the old and new states of the document.</p>

<p>Additionnaly, Flip will store this transaction in a <em>Push Stack</em> ready to be pushed to the remote server.</p>

<p>If you then call <code>push</code> on the document, and the document is set up to work with a remote server, Flip will send all the commits to that server, so that they can be executed by the server and arbitrated.</p>

<p>Similarly, to receive the changes available on the remote server done by another user, or to know if the change on a document were acknowledge or denied, one will call <code>pull</code> on the document to receive and merge this changes into your local document. Internally, the transport layer will regurarly fetch the server for changes and store them in a <em>Pull Stack</em>. Calling <code>pull</code> will simply execute each element of the pull stack.</p>

<p>Generally, you won't push to the remote server for every single commit you do. For example in the previous example, if a user drags a clip on the track by changing its position, then you may want to advertise those changes to the outside world only when the user has finished its gesture by releasing the mouse button. In this case you might do commit for every mouse moves, and then only push to the remote server once the user has released the mouse button. Depending on the case, you might also want not to commit on every mouse moves, and commit and push at the same time when the user released the mouse button.</p>

<p>Generally, you would pull almost constantly from the server.</p>

<p>The next sections will show how to set up concretely the code to work with a remote server.</p>

<h2 id="remote">Working with a Remote Server, Client Part</h2>

<p>Documents connect to a remote a server through a <em>Transport</em>. Flip can support many transports methods through its transport abstraction. For a simple TCP socket, one can use <code>TransportSimpleSocket</code> in <code>flip/contrib</code>. This will be the class used in the following examples.</p>

```c++
#include "flip/contrib/TransportSimpleServer.h"

void  run ()
{
   Document document (Model::use (), 123456789ULL, 'OmSt', 'gui ');
   TransportListener listener;
   TransportSimpleSocket transport (listener, document, "localhost", 9000);   (1)

   transport.process ();                                                      (2)

   document.pull ();                                                          (3)

   Root & root = document.root <Root> ();
   root.happiness_level = 100.0;
   document.commit ();

   document.push ();                                                          (4)

   transport.process ();
}
```

<ol>
<li>Connect to <code>localhost</code> on port <code>9000</code>. A listener can be attached to listen on different transport events like document downloading progress, I/O errors, etc.</li>
<li><code>process</code> allows for this transport implementation to write and read from the socket as needed</li>
<li>this call to <code>pull</code> will replace the current document with the one from the remote server</li>
<li>this call to <code>push</code> will send the hapinnes level change to the document server</li>
</ol>

<p>The code above implies that a Flip server is running on <code>localhost</code> port <code>9000</code>. The next section will show how to set up this server.</p>

<h2 id="server">Working with a Remote document, Server Part</h2>

<p>In this example, the server side of <code>TransportSimpleSocket</code> is used.</p>

```c++
void run ()
{
   DocumentValidatorVoid validator;                         (1)
   DocumentServer document (Model::use (), validator);      (2)

   Root & root = document.root <Root> ();
   root.happiness_level = 42.0;

   document.commit ();                                      (3)

   TransportSimpleServer transport (*this, document, 9000); (4)

   for (;;)
   {
      transport.process ();                                 (5)
   }
}
```

<ol>
<li>Set up a validator. Validator are used to ensure that the document is always in a valid state. This will be discussed in the next section</li>
<li>Set up a <code>DocumentServer</code>. A document server is a special kind of <code>Document</code> already setup for server use</li>
<li>The document was prepared with an initial value for happinness, but it could have been loaded from a location, modified, converted, etc.</li>
<li>Set up the server socket and start listening for clients</li>
<li>Allows the server to process incoming client request</li>
</ol>

<h2 id="validate">Validating Transactions</h2>

<p>When a single user is working in a document, it can somehow be assumed that the changes made for the document are going to be valid, from the model logic point of view. While this can be ensured by proper coding in the single user case, there is no way to make sure of it in a concurrent environment.</p>

<p>To solve this problems, Servers need to run validation code. The code will ensure that the new state of the document is valid from the model logic point of view. If the document is not valid, the validator will inform it to the Flip system which will rollback the transaction, ensuring that the document returns to the last known valid state.</p>

<p>Validating the model is very similar to observing it. Actually the code to traverse the model will be exactly similar to the one to observe it. When the validator encounters an error, it will throw to notify the Flip system that the document state it is looking at is not valid. The convenience macro <code>flip_VALIDATION_FAILED</code> is provided for this matter.</p>

<h2 id="bind">Declaring and Binding a Validator</h2>

<p>Validators are declared in a similar way to observers :</p>

```c++
class Validator : public flip::DocumentValidator <Song>                       (1)
{
public:
   virtual void validate (Song & song) override;                              (2)
}

void  run ()
{
   Validator validator;
   DocumentServer document (Model::use (), validator);                        (3)
}
```

<ol>
<li>Make a validator by inheriting from <code>DocumentValidator</code></li>
<li>Override the pure virtual function declared in <code>DocumentValidator</code></li>
<li>Attach the observer to the document</li>
</ol>

<p>Now, every time the document will be changed and the server receives this modification, <code>validate</code> will be fired.</p>

<h2 id="validator">Writing Validation Code</h2>

<p>In the example, we might want to ensure that the clip positions are always positive or zero, and that the durations are always strictly positive. Implementing this validation scheme would be done like in the following code :</p>

```c++
void  Validator::validate (Song & song)
{
   if (song.tempo.changed ())
   {
      if (song.tempo < 20) flip_VALIDATION_FAILED ("incorrect tempo");
   }

   if (song.tracks.changed ())
   {
      for (auto && track : song.tracks)
      {
         if (track.changed ())
         {
            for (auto && clip : track.clips)
            {
               if (clip.changed ())
               {
                  if (clip.position < 0.0) flip_VALIDATION_FAILED ("incorrect position");
                  if (clip.duration <= 0.0) flip_VALIDATION_FAILED ("incorrect duration");
               }
            }
         }
      }
   }
}
```

<p>The next chapter, <a href="../guide/misc.md">More Fun with Flip</a> will guide you through more advanced use of Flip.</p>

<p><sup><a href="observe.md">previous</a> | <a href="misc.md">next</a></sup></p>

