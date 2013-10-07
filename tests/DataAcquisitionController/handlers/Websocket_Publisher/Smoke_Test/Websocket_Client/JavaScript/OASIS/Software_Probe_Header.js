/**
* @struct Software_Probe_Header
*
* Header for all software probes. It contains infomration related
* to the latest collect metrics.
*/

//
// Constructor
//
function Software_Probe_Header()
{
  /// UUID assigned to this software probe.
  this.uuid_ = new UUID();

  /// The lastest timestamp.
  this.last_ts_ = new Time_Value();

  /// The current sequence number for the data.
  this.seqnum_ = 0;

  /// The state of the software probe.
  this.state_ = 0;

  /// The size of the software probe's data.
  this.datasize_ = 0;
} // end_of_Software_Probe_Header

Software_Probe_Header.prototype.to_string = function()
{
  var uuid_string = sprintf("%8.8x-%4.4x-%4.4x-%2.2x%2.2x-%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x",
                            []);
}
