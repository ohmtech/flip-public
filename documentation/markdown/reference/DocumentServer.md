<p><sup><a href="DocumentObserver.md">previous</a> | <a href="DocumentValidator.md">next</a></sup></p>

<h1>DocumentServer Class Reference</h1>

<table><tr><td>Declared in</td><td><code>flip/DocumentServer.h</code></td></tr>
</table>

```c++
class DocumentServer;
```

<p><code>flip::DocumentServer</code> is a type that represents a flip document on the server side.</p>

<h2>Member Functions Synopsys</h2>

<table><tr><td><a href="#member-function-constructor">Constructor</a></td><td>Constructs the <code>DocumentServer</code></td></tr>
<tr><td><a href="#member-function-destructor">Destructor</a></td><td>Destructs the <code>DocumentServer</code></td></tr>
<tr><td><code><a href="#member-function-listen_connecting">listen_connecting</a></code></td><td>Reacts just before a client join the document</td></tr>
<tr><td><code><a href="#member-function-listen_connected">listen_connected</a></code></td><td>Reacts just after a client join the document</td></tr>
<tr><td><code><a href="#member-function-listen_disconnected">listen_disconnected</a></code></td><td>Reacts just after a client left the document</td></tr>
<tr><td><code><a href="#member-function-send_tx_if">send_tx_if</a></code></td><td>Send a transaction to every client meeting a condition</td></tr>
<tr><td><code><a href="#member-function-reply_signal">reply_signal</a></code></td><td>Replies to a signal sent from one client</td></tr>
<tr><td><code><a href="#member-function-send_signal_if">send_signal_if</a></code></td><td>Broadcasts a signal selectively</td></tr>
</table>

<h3>Manipulating</h3>

<table><tr><td><code><a href="#member-function-set_label">set_label</a></code></td><td>Sets the label of the current modifications of the document</td></tr>
<tr><td><code><a href="#member-function-set_metadata">set_metadata</a></code></td><td>Sets the metadata of the current modifications of the document</td></tr>
<tr><td><code><a href="#member-function-commit">commit</a></code></td><td>Commits the current modifications of the document</td></tr>
<tr><td><code><a href="#member-function-revert">revert</a></code></td><td>Reverts the current modifications of the document</td></tr>
<tr><td><code><a href="#member-function-push">push</a></code></td><td>Pushes the transactions to the upstream</td></tr>
<tr><td><code><a href="#member-function-pull">pull</a></code></td><td>Pulls document modifications from the upstream</td></tr>
</table>

<h3>Transaction</h3>

<table><tr><td><code><a href="#member-function-execute_forward">execute_forward</a></code></td><td>Executes a transaction on a document in forward direction</td></tr>
<tr><td><code><a href="#member-function-execute_backward">execute_backward</a></code></td><td>Executes a transaction on a document in backward direction</td></tr>
<tr><td><code><a href="#member-function-execute_correct_forward">execute_correct_forward</a></code></td><td>Executes and corrects a transaction on a document in forward direction</td></tr>
<tr><td><code><a href="#member-function-execute_correct_backward">execute_correct_backward</a></code></td><td>Executes and corrects a transaction on a document in backward direction</td></tr>
</table>

<h3>Observing</h3>

<table><tr><td><code><a href="#member-function-controller">controller</a></code></td><td>Returns the current controller source of modification</td></tr>
</table>

<h3>Input/Ouput</h3>

<table><tr><td><code><a href="#member-function-write">write</a></code></td><td>Write the current state of the document to an intermediate representation format</td></tr>
<tr><td><code><a href="#member-function-read">read</a></code></td><td>Read from an intermediate representation format</td></tr>
</table>

<h3>Accessing Objects</h3>

<table><tr><td><code><a href="#member-function-root">root</a></code></td><td>Returns the root object</td></tr>
<tr><td><code><a href="#member-function-object">object</a></code></td><td>Returns an object given its unique flip reference number</td></tr>
<tr><td><code><a href="#member-function-object_ptr">object_ptr</a></code></td><td>Returns an object pointer given its unique flip reference number, or <code>nullptr</code></td></tr>
</table>

<h2>Member Functions</h2>

<h3 id="member-function-constructor">Constructor</h3>
```c++
DocumentServer (const DataModelBase & data_model, DocumentValidatorBase & validator, uint64_t session_id);
```

<p>Constructs the document from a data model and a validator using unique session identifier.</p>

<p>The data model represents the blueprint or template the document is going to rely on. The data model is previously defined and used for the document.</p>

<p>The session identifier represents a unique number accross documents uniquely identifying this document. When the document is changed on the server side, the session identifier is used as a way to identify the server acting as a user.</p>

<p>Example, server side :</p>

```c++
#include "flip/contrib/transport_tcp/PortTransportServerTcp.h"

// Setup a server for session number 1234567890123
DocumentValidatorVoid validator;
DocumentServer document_server (Model::use (), validator, 1234567890123ULL);

// Setup a socket listening on TCP port 9090 to accept new connections.
PortTransportServerTcp port (document_server, 9090);

for (;;)
{
   // process incoming connections and transfers
   port.process ();
}
```

<p>Example, client side :</p>

```c++
#include "flip/contrib/transport_tcp/CarrierTransportSocketTcp.h"

Document document (Model::use (), 123456789ULL, 'appl', 'gui ');

// Setup a socket connecting on TCP port 9090 of server.
CarrierTransportSocketTcp carrier (document, "flip.myserver.com", 9090);

for (;;)
{
   // process incoming connections and transfers
   carrier.process ();
}
```

<h3 id="member-function-destructor">Destructor</h3>
```c++
~DocumentServer ();
```

<p>Destructor.</p>

<h3 id="member-function-listen_connecting"><code>listen_connecting</code></h3>
```c++
void  listen_connecting (std::function <void (PortBase &)> func);
```

<p>Example :</p>

```c++
DocumentServer server = ...;

// listen on connections and create a specific Client class
// in the root of the document for private data

server.listen_connecting ([&server](PortBase & port){
   Root & root = server.root <Root> ();

   if (root._clients.count_if ([&port](Client & client){
      return client.user () == port.user ();
   }) == 0)
   {
      root._clients.emplace (port.user ());
   }

   Transaction tx = server.commit ();
   server.send_tx_if (tx, [](PortBase &){return true;});
});
```

<h3 id="member-function-listen_connected"><code>listen_connected</code></h3>
```c++
void  listen_connected (std::function <void (PortBase &)> func);
```

<p>Example :</p>

```c++
DocumentServer server = ...;

// hypothetic class representing a monitoring system for administration
MonitoringSystem monitor = ...;

server.listen_connected ([&monitor](PortBase & port){
   monitor.add_user (port.user ());
});
```

<h3 id="member-function-listen_disconnected"><code>listen_disconnected</code></h3>
```c++
void  listen_disconnected (std::function <void (PortBase &)> func);
```

<p>Example :</p>

```c++
DocumentServer server = ...;

// hypothetic class representing a monitoring system for administration
MonitoringSystem monitor = ...;

listen_disconnected ([&monitor](PortBase & port){
   monitor.remove_user (port.user ());
});
```

<h3 id="member-function-send_tx_if"><code>send_tx_if</code></h3>
```c++
template <class UnaryPredicate>  void  send_tx_if (const Transaction & tx, UnaryPredicate p);
```

<p>Send transaction <code>tx</code> to every client meeting condition using unary function <code>p</code>.</p>

<p>Example :</p>

```c++
DocumentServer server = ...;

// listen on connections and create a specific Client class
// in the root of the document for private data

server.listen_connecting ([&server](PortBase & port){
   Root & root = server.root <Root> ();

   if (root._clients.count_if ([&port](Client & client){
      return client.user () == port.user ();
   }) == 0)
   {
      root._clients.emplace (port.user ());
   }

   Transaction tx = server.commit ();
   server.send_tx_if (tx, [](PortBase &){return true;});
});
```

<p>Sends the transaction to all attached clients.</p>

<h3 id="member-function-reply_signal"><code>reply_signal</code></h3>
```c++
void  reply_signal (const SignalData & data);
```

<p>Replies to a signal sent from a client, when the signal on the client is configured on the client side to pass through local machine boundaries.</p>

<p>Example :</p>

```c++
class Root : public Object
{
   enum
   {
      Signal_SIGN_UPLOAD_REQUEST = 0,
      Signal_SIGN_UPLOAD_SIGNATURE,
   };

   // from client to server
   Signal <std::string> signal_sign_upload_request;

   // from client to server
   Signal <std::string> signal_sign_upload_signature;
};
```

<p>The following example demonstrates a client sending a signal to the server to sign a request to upload data on a server.</p>

```c++
/*   Client side   */

// don't forget to move cnx so that it is not destroyed
auto cnx = root.signal_sign_upload_signature.connect ([](std::string signature){
   // the client receives the reply to its sign request
});

// send the sign request
root.signal_sign_upload_request ("string to sign");
```

<p>The following example shows how a server is handling the signal and reply to it.</p>

```c++
/*   Server side   */

DocumentServer = ...;

// don't forget to move cnx so that it is not destroyed
auto cnx = root.signal_sign_upload_request.connect ([&root, &server](std::string str_to_sign){
   auto signature = sign_request (str_to_sign);

   server.reply_signal (
      root.signal_sign_upload_signature.make (signature)
   ;
});
```

<h3 id="member-function-send_signal_if"><code>send_signal_if</code></h3>
```c++
template <class UnaryPredicate>
void  send_signal_if (const SignalData & data, UnaryPredicate p);
```

<p>Broadcasts a signal selectively to clients.</p>

<p>Example :</p>

<p>The following example shows how a server is handling the previous signal but broadcast the signature to every connected clients.</p>

```c++
/*   Server side   */

DocumentServer = ...;

// don't forget to move cnx so that it is not destroyed
auto cnx = root.signal_sign_upload_request.connect ([&root, &server](std::string str_to_sign){
   auto signature = sign_request (str_to_sign);

   server.send_signal_if (
      root.signal_sign_upload_signature.make (signature),
      [](){return true;}
   ;
});
```

<h3 id="member-function-set_label"><code>set_label</code></h3>
```c++
void  set_label (std::string label);
```

<p>Sets the label (ie. name) of the current modifications of the document. This metadata will be added to the transaction at <code>commit</code> stage.</p>

<p>This is typically use to display the undo/redo name in the Edit menu of the menubar.</p>

<p>If called multiple times before <code>commit</code>, only the last state of the metadata is taken into account at <code>commit</code> stage.</p>

<p>Example :</p>

```c++
Root & root = document.root <Root> ();
root.notes.emplace <Note> (2.0, 4.0);

document.set_label ("Add note");

Transaction tx = document.commit ();
// the transaction contains the new note modification in 'root.notes'
// as well as the metadata label "Add note"
```

<h3 id="member-function-set_metadata"><code>set_metadata</code></h3>
```c++
void  set_metadata (std::string key, std::string value);
```

<p>Sets the metadata <code>value</code> for <code>key</code> of the current modifications of the document. This metadata will be added to the transaction at <code>commit</code> stage.</p>

<p>If called multiple times before <code>commit</code>, only the last state of the metadata is taken into account at <code>commit</code> stage.</p>

<p>This is a more general version of <code>set_label</code>. Actually, <code>set_label</code> calls this methods with the <code>key</code> <code>"label"</code>.</p>

<p>This can be used to present even more textual informations for undo/redo operations, for example detailing the nature of the change.</p>

<h3 id="member-function-commit"><code>commit</code></h3>
```c++
Transaction commit ();
```

<p>Commits the current modifications of the document and returns the resulting transaction. The modifications are validated through the validator if the document has one, and will throw if the document state is invalid.</p>

<p>Once the function returns, the document is valid from a validation point of view and the transaction is put on the push stack for later upstream synchronization.</p>

<h3 id="member-function-revert"><code>revert</code></h3>
```c++
void revert ();
```

<p>Reverts the current modifications of the document.</p>

<h3 id="member-function-push"><code>push</code></h3>
```c++
void push ();
```

<p>Pushes the transactions in the push stack to the upstream and empty the push stack. If no upstream is present then this function will just empty the push stack.</p>

<blockquote><h6>W A R N I N G</h6> Even if not connected to an upstream, it is important to call <code>push</code>    regularly to empty the push stack.</blockquote>

<h3 id="member-function-pull"><code>pull</code></h3>
```c++
void pull ();
```

<p>Pulls document modifications from the upstream. If no upstream is present then this function does nothing.</p>

<p>If the document contains modifications, they are temporarily saved and rollbacked, then external modifications are applied, and the local modifications are reapplied. If the local modifications cannot be reapplied, then they are dropped silently.</p>

<h3 id="member-function-execute_forward"><code>execute_forward</code></h3>
```c++
bool  execute_forward (const Transaction & tx, bool undo_mode_flag = false);
```

<p>Executes a transaction on a document in forward direction. Returns <code>true</code> if the execution was successful, <code>false</code> otherwise. Executing a transaction does not call the validator nor commits the transaction.</p>

<p>If <code>undo_mode_flag</code> is set to <code>true</code>, then the instructions of the transaction that are marked to be out of undo (through a prior call to <code>disable_in_undo</code>) won't be executed unless the top object disabled in undo has a container parent enabled in undo and the top object was either added or removed. This is the default mode when using flip <code>History</code> class.</p>

<h3 id="member-function-execute_backward"><code>execute_backward</code></h3>
```c++
bool  execute_backward (const Transaction & tx, bool undo_mode_flag = false);
```

<p>Executes a transaction on a document in backward direction. Returns <code>true</code> if the execution was successful, <code>false</code> otherwise. Executing a transaction does not call the validator nor commits the transaction.</p>

<p>If <code>undo_mode_flag</code> is set to <code>true</code>, then the instructions of the transaction that are marked to be out of undo (through a prior call to <code>disable_in_undo</code>) won't be executed. This is the default mode when using flip <code>History</code> class.</p>

<h3 id="member-function-execute_correct_forward"><code>execute_correct_forward</code></h3>
```c++
bool  execute_correct_forward (const Transaction & tx, bool undo_mode_flag = false);
```

<p>Executes and corrects a transaction on a document in forward direction. Returns <code>true</code> if the execution was successful, <code>false</code> otherwise. Executing a transaction does not call the validator nor commits the transaction.</p>

<p>Correcting allows to force a transaction to execute if possible. Transaction instructions are similar to compare & exchange processor instructions. Only if the old state of the document matches the instruction old value then the new value is applied. In this case correcting allows the virtual machine to force the execution and change the instruction to match virtual machine constraints.</p>

<p>If <code>undo_mode_flag</code> is set to <code>true</code>, then the instructions of the transaction that are marked to be out of undo (through a prior call to <code>disable_in_undo</code>) won't be executed. This is the default mode when using flip <code>History</code> class.</p>

<h3 id="member-function-execute_correct_backward"><code>execute_correct_backward</code></h3>
```c++
bool  execute_correct_forward (const Transaction & tx, bool undo_mode_flag = false);
```

<p>Executes and corrects a transaction on a document in backward direction. Returns <code>true</code> if the execution was successful, <code>false</code> otherwise. Executing a transaction does not call the validator nor commits the transaction.</p>

<p>Correcting allows to force a transaction to execute if possible. Transaction instructions are similar to compare & exchange processor instructions. Only if the old state of the document matches the instruction old value then the new value is applied. In this case correcting allows the virtual machine to force the execution and change the instruction to match virtual machine constraints.</p>

<p>If <code>undo_mode_flag</code> is set to <code>true</code>, then the instructions of the transaction that are marked to be out of undo (through a prior call to <code>disable_in_undo</code>) won't be executed. This is the default mode when using flip <code>History</code> class.</p>

<h3 id="member-function-controller"><code>controller</code></h3>
```c++
Controller  controller () const;
```

<p>When called from document observer callback, returns the current controller source of modification. If the callback resulted from a <code>pull</code> operation, the returned controller is the last one from the pull queue.</p>

```c++
enum class Controller
{
   NONE,          (1)
   SELF,          (2)
   UNDO,          (3)
   READ,          (4)
   LOCAL,         (5)
   EXTERNAL,      (6)
   ACKNOWLEDGED,  (7)
   DENIED,        (8)
};
```

<ol>
<li>Returned when called outside of an observer callback</li>
<li>Returned when originated to this document</li>
<li>Returned when originated from an undo operation (<code>History</code>)</li>
<li>Returned when originated from a read operation</li>
<li>Returned when originated from a local change</li>
<li>Returned when originated from a remote change</li>
<li>Returned when the server accepted one of the pushed transaction</li>
<li>Returned when the server rejected one of the pushed transaction</li>
</ol>

<h3 id="member-function-write"><code>write</code></h3>
```c++
BackEndIR   write ();
```

<p>Write the current state of the document (with its potential modifications) to an intermediate representation format backend.</p>

<p>The resulting object can be used with concrete backends format such as <code>BackEndBinary</code> or <code>BackEndMl</code> to store them on a media.</p>

<p>See <a href="../reference/BackEndMl.md"><code>BackEndMl</code></a> or <a href="../reference/BackEndBinary.md"><code>BackEndBinary</code></a> for an example of use of this method.</p>

<h3 id="member-function-read"><code>read</code></h3>
```c++
void  read (BackEndIR & backend);
```

<p>Read from an intermediate representation format backend. Internally this will create a transaction that represents the difference between the new backend and the current state of the document. As such, the document modification are not commited at the end of this operation.</p>

<p>See <a href="../reference/BackEndMl.md"><code>BackEndMl</code></a> or <a href="../reference/BackEndBinary.md"><code>BackEndBinary</code></a> for an example of use of this method.</p>

<h3 id="member-function-root"><code>root</code></h3>
```c++
template <class T>   T & root ();
```

<p>Returns the root object of the document.</p>

<h3 id="member-function-object"><code>object</code></h3>
```c++
template <class T>   T & object (const Ref & ref);
```

<p>Returns an object given its unique flip reference number. The function will throw if the reference number does not exist in the document or if the resulting object cannot be casted to <code>T</code>.</p>

<p>See <a href="../reference/Ref.md"><code>Ref</code></a> for more details.</p>

<h3 id="member-function-object_ptr"><code>object_ptr</code></h3>
```c++
template <class T>   T * object_ptr (const Ref & ref);
```

<p>Returns an object given its unique flip reference number. The function will return <code>nullptr</code> if the reference number does not exist in the document or if the resulting object cannot be casted to <code>T</code>.</p>

<p>See <a href="../reference/Ref.md"><code>Ref</code></a> for more details.</p>

<p><sup><a href="DocumentObserver.md">previous</a> | <a href="DocumentValidator.md">next</a></sup></p>

