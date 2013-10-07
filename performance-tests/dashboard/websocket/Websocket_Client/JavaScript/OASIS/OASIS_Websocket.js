/**
* @class OASIS_Webscket
*
*/

//
//create_websocket_connection
//
function create_websocket_connection (host, port)
{
  var url = "ws://" + host + ":" + port + "/";
  var ws = new Websocket(url);
  ws.onopen += handle_open_connection;
  ws.onmessage += handle_input;
  ws.onclose += handle_close;

  return ws;
}

//
// Initializing Constructor
//
function OASIS_Websocket (host, port)
{
  this.host_ = host;
  this.port_ = port;
  this.ws = create_websocket_connection (this.host_,this.port_);
}

//
//
//