<p><sup><a href="observe.md">previous</a> | <a href="remote.md">next</a></sup></p>

<h1>Signalling the Model</h1>

<p>Now that we can control the model with persistent data, this chapter exposes how to control the model with non-persistent data, that is data that is not going to be saved. There multiple ways to achieve that in flip, with slightly different meaning, exposed here.</p>

<p>This chapter will use the model declared in the chapter <a href="../guide/declare.md">Declaring the Model</a>.</p>

<h2 id="which"><code>Signal</code> and <code>Message</code></h2>

<p>Flip has two signal types : <a href="../reference/Signal.md"><code>Signal</code></a> and <a href="../reference/Message.md"><code>Message</code></a>. They operate in a relative similar ways, but have different meanings.</p>

<h3 id="which-message"><code>Message</code></h3>

<p><a href="../reference/Message.md"><code>Message</code></a> is a flip type. It does not store data, but allows to share non-persitent data between clients. For this reason, it is part of the document model.</p>

<p>When a <code>Message</code> is signalled, the content of the data is shared with every documents and clients connected to the same document, but the data itself is not saved within the document.</p>

<p>A <code>Message</code> describes a transient change of state of a flip Object. Receiving the data sent is done through the observer, as a <code>Message</code> is part of the model, which means that the data from a message is in a transaction where over members might be changed. This allows to receive synchronously changes of the model, that would be hard to manage with a <code>Signal</code>.</p>

<p>Let's take an example to illustrate this point. Let's consider a play head in a audio or video application. From a feature point of view, the play head has a position and a state (playing or not playing). The position expresses the change in the model, not the actual position as shown in the view.</p>

<p>If suddenly the user want to change both the position and the state of the play head, then using a <code>Message</code> ensure that those two properties are going to be changed synchronously and transactionally into the model.</p>

<p>This is not the case with <code>Signal</code> where those changes would come one after the other, possibly in a different order.</p>

<p>Example :</p>

```c++
class PlayHead : public Object
{
public:
   enum State
   {
      State_STOPPED = 0,
      State_PLAYING,
   };

   Float position;
   Message <State> state;
};

// controlling the model, jumping to position 2.0
// and playing at the same time

auto & playhead = song.playhead;
playhead.position = 2.0;
playhead.state.send (PlayHead::State_PLAYING);

playhead.document ().commit ();


// observing the model, this allow to see the
// changes as a transaction

void  document_changed (PlayHead & playhead)
{
   if (playhead.position.changed ())
   {
      // ...
   }

   if (playhead.state.changed ())
   {
      playhead.state.get ([&](bool forward_flag, State state) {
         // ...
      });
   }
}
```

<p>Finally, because it is part of the document model, <code>Message</code> has a <code>forward_flag</code> as part of its function definition, to allow for the observer to take the direction of execution of the transaction to be taken into account. The semantic of backward for a <code>Message</code> data depends on the semantic of the model. The only rule is to have the proper behavior if the transaction containing the <code>Message</code> is refused by the server so rollbacked locally, or the meaning of undoing a transaction when the transaction contains operations over a <code>Message</code>.</p>

<h3 id="which-signal"><code>Signal</code></h3>

<p>On the other hand, <a href="../reference/Signal.md"><code>Signal</code></a> is not a flip type. It also does not store data, and the data is not shared between other clients. It is not part of the document model.</p>

<p>When a <code>Signal</code> is signalled, the content of the data is shared only with every documents connected through a <code>Hub</code> on the local machine, and the data itself is not saved within the document.</p>

<p>A <code>Signal</code> describes a signal directed to a flip Object.</p>

<p>Receiving the data sent is done with the help of a signal connection which is outside the model, and is not received through the <code>document_changed</code> virtual method of the observer. Therefore it is not synchronous to changes of the model.</p>

<p>Because of the way it internally works, <code>Signal</code> is also preferred when the amount of data to exchange per second can be enormous.</p>

<p>Let's take the previous example and let's say that the realtime position of the playhead (not the one reflected in the model) is going to be signaled from the audio engine to the GUI using a <code>Signal</code>.</p>

<p>When the play head is constructed, the observer of the GUI will set up a signal connection to receive the realtime position, as illustrated below.</p>

```c++
class PlayHead : public Object
{
public:
   enum
   {
      Signal_RT_POSITION = 0,
   };

   PlayHead () : signal_rt_position (Signal_RT_POSITION, *this) {}

   Signal <double> signal_rt_position;
};

void  document_changed (PlayHead & playhead)
{
   if (playhead.added ())
   {
      // Store the SignalConnection in an entity

      playhead.entity ().emplace <SignalConnection> (
         playhead.signal_rt_position.connect ([](double position){
            // update realtime position in the GUI
         });
      );
   }

   if (playhead.removed ())
   {
      playhead.entity ().erase <SignalConnection> ();
   }
}

// From audio engine :

double position = audio_engine.get_rt_position ();

playhead.signal_rt_position (position);
```

<p>The signal also decouple the sender from the receiver, in the sense that the sender does not need to know who is going to receive the data, and even is the data is going to be received at all.</p>

<p>This is also a safe mechanism, if an object is already deleted in a document, while still present in another document : if the signal does not have a recipient anymore, it is silently dropped.</p>

<p>The next chapter, <a href="../guide/remote.md">Working with a Remote Server</a> will guide you through setting up a collaboration network.</p>

<p><sup><a href="observe.md">previous</a> | <a href="remote.md">next</a></sup></p>

