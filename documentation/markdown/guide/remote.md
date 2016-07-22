<p><sup><a href="signal.md">previous</a> | <a href="misc.md">next</a></sup></p>

<h1>Working with a Remote Server</h1>

<p>At this point, you are able to declare a model and interact with it by controlling it and observing it. But still this happens only on a local computer.</p>

<p>This chapter exposes how Flip works with a remote server and brings collaboration features to your application.</p>

<h2 id="workflow">Commit/Push/Pull Model</h2>

<p>When you call <code>commit</code> on a document, Flip will create the transaction that represents the change between the old and new states of the document.</p>

<p>Additionnaly, Flip will store this transaction in a <em>Push Stack</em> ready to be pushed to the remote server.</p>

<p>If you then call <code>push</code> on the document, and the document is set up to work with a remote server, Flip will send all the commits to that server, so that they can be executed by the server and arbitrated.</p>

<p>Similarly, to receive the changes available on the remote server done by another user, or to know if the change on a document were acknowledge or denied, one will call <code>pull</code> on the document to receive and merge this changes into your local document. Internally, the transport layer will regurarly fetch the server for changes and store them in a <em>Pull Stack</em>. Calling <code>pull</code> will simply execute each element of the pull stack.</p>

<p>Generally, you won't push to the remote server for every single commit you do. For example in the previous example, if a user drags a clip on the track by changing its position, then you may want to advertise those changes to the outside world only when the user has finished its gesture by releasing the mouse button. In this case you might do commit for every mouse moves, and then only push to the remote server once the user has released the mouse button. Depending on the case, you might also want not to commit on every mouse moves, and commit and push at the same time when the user released the mouse button.</p>

<p>Additionally, one can <code>squash</code> the Push Stack, so that all transactions previously commited are squashed to one transaction before this transaction is pushed to the server. This is particularly useful in the case where the same values are changed over and over in a gesture, so that the resulting transaction is far smaller than every commits.</p>

<p>Generally, you would pull almost constantly from the server.</p>

<p>The next sections will show how to set up concretely the code to work with a remote server.</p>

<h2 id="remote">Working with a Remote Server, Client Part</h2>

<p>Documents connect to a remote a server through a <em>Transport</em>. Flip can support many transports methods through its transport abstraction.</p>

<p>For a simple TCP socket, one can use <code>CarrierTransportSocketTcp</code> in <code>flip/contrib/transport_tcp</code>. This will be the class used in the following examples.</p>

<p>A client is assigned a <em>user identifier</em>. This user identifier must be unique for every user connecting to the same session. Typically this can be a facebook user number or an OpenId unique identifier. For a quick test, using a random generator might be good enough.</p>

<p>Then the client is going to connect to a session, with a <em>session identifier</em>. A session represents a document on the server side, and is usually meant to be persistent.</p>

```c++
#include "flip/contrib/transport_tcp/CarrierTransportSocketTcp.h"

void  run (uint64_t user_id, uint64_t session_id)
{
   Document document (Model::use (), user_id, 'appl', 'gui ');                   (1)
   CarrierTransportSocketTcp carrier (document, session_id, "localhost", 9000);  (2)

   carrier.process ();                                                           (3)

   document.pull ();                                                             (4)

   Root & root = document.root <Root> ();
   root.happiness_level = 100.0;
   document.commit ();

   document.push ();                                                             (5)

   carrier.process ();
}
```

<ol>
<li>Create a new document for <code>user_id</code>. <code>user_id</code> must be unique for every    user connecting to the session</li>
<li>Connect to <code>localhost</code> on port <code>9000</code>, for <code>session_id</code></li>
<li><code>process</code> allows for this transport implementation to write and read from the socket as needed</li>
<li>this call to <code>pull</code> will replace the current document with the one from the remote server</li>
<li>this call to <code>push</code> will send the happiness level change to the document server</li>
</ol>

<blockquote><h6>Note</h6> The code above is simplified, as a single <code>process</code> code on a transport carrier    does not guarantee that the socket will be able to send or receive all data.</blockquote>

<p>The code above implies that a Flip server is running on <code>localhost</code> port <code>9000</code>. The next section will show how to set up this server.</p>

<h2 id="server">Working with a Remote document, Server Part</h2>

<p>In this example, <code>ServerSimple</code> from <code>flip/contrib</code> is used. It is a simple server that allows to host multiple sessions, and is running all in one process. This is probably not suitable for production quality, but nethertheless very handy to set up a flip server quickly.</p>

```c++
#include "flip/contrib/DataConsumerFile.h"
#include "flip/contrib/DataProviderFile.h"
#include "flip/contrib/ServerSimple.h"
#include "flip/BackEndBinary.h"


std::string path (uint64_t session_id)
{
   return std::string ("/sessions/") + std::to_string (session_id);
}

void run ()
{
   ServerSimple server (Model::use (), 9000);               (1)

   server.bind_validator_factory ([](uint64_t session_id){
      return std::make_unique <MyModelValidator> ();        (2)
   });

   server.bind_init ([](uint64_t session_id, DocumentBase & document){
      Root & root = document.root <Root> ();
      root.happiness_level = 42.0;                          (3)
   });

   server.bind_read ([](uint64_t session_id){
      BackEndIR backend;

      auto session_path = path (session_id);

      if (path_exists (session_path))
      {
         DataProviderFile provider (session_path.c_str ());

         backend.register_backend <BackEndBinary> ();
         backend.read (provider);
      }

      return backend;                                       (4)
   });

   server.bind_write ([](uint64_t session_id, const BackEndIR & backend){
      auto session_path = path (session_id);

      DataConsumerFile consumer (session_path.c_str ());

      backend.write <BackEndBinary> (consumer);             (5)
   });

   server.run ();                                           (6)
}
```

<ol>
<li>Set up the server to listen on port <code>9000</code></li>
<li>Bind the validator factory. This is run every time a new session is opened</li>
<li>Bind the document initiator. When no session is already present (see 4. below),    it will create a non-empty initial document, should it be needed.</li>
<li>Bind the document reader. Here it is using a <code>DataProviderFile</code>    with the <code>BackEndBinary</code> production document format.    If the returned backend is empty, then the document initiator (see 3. above) is called.    This is also where you would convert your document to the current model version if needed.</li>
<li>Bind the document writer. Here it is using a <code>DataConsumerFile</code>    with the <code>BackEndBinary</code> production document format</li>
<li>Finally run the server. This function will allow the server to process incoming client request</li>
</ol>

<h2 id="validate">Validating Transactions</h2>

<p>When a single user is working in a document, it can somehow be assumed that the changes made for the document are going to be valid, from the model logic point of view. While this can be ensured by proper coding in the single user case, there is no way to make sure of it in a concurrent environment.</p>

<p>To solve this problems, Servers need to run validation code. The code will ensure that the new state of the document is valid from the model logic point of view. If the document is not valid, the validator will inform it to the Flip system which will rollback the transaction, ensuring that the document returns to the last known valid state.</p>

<p>Validating the model is very similar to observing it. Actually the code to traverse the model will be exactly similar to the one to observe it. When the validator encounters an error, it will throw to notify the Flip system that the document state it is looking at is not valid. The convenience macro <code>flip_VALIDATION_FAILED</code> is provided for this matter.</p>

<h2 id="bind">Declaring and Binding a Validator</h2>

<p>Validators are declared in a similar way to observers :</p>

```c++
#include "flip/DocumentValidator.h"

class Validator : public flip::DocumentValidator <Song>                       (1)
{
public:
   virtual void validate (Song & song) override;                              (2)
}

void  run ()
{
   ServerSimple server (Model::use (), 9000);

   server.bind_validator_factory ([](uint64_t session_id){
      return std::make_unique <Validator> ();                                 (3)
   });
}
```

<ol>
<li>Make a validator by inheriting from <code>DocumentValidator</code></li>
<li>Override the pure virtual function declared in <code>DocumentValidator</code></li>
<li>Create a new <code>Validator</code> that will be attached to every new document created by the server</li>
</ol>

<p>Now, every time the document session will be changed and the server receives this modification, <code>validate</code> will be fired.</p>

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

<p><sup><a href="signal.md">previous</a> | <a href="misc.md">next</a></sup></p>

