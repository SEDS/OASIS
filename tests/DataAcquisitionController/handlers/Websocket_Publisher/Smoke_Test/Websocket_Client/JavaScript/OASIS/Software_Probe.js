/**
* @class Software_Probe
*
* Base class for all software probes stubs. The software probe stub
* constains the metadata for a given probe. In addition, it contains
* a method for recalling a software probe's data that was previously
* packaged by an implementation.
*/

//
// Constructor
//
function Software_Probe()
{
  /// Metadata associated with the software probe.
  this.header_ = new Software_Probe_Header();

  /// Instance name assigned to the probe.
  this.name_ = "";
}

Software_Probe.MAX_ALIGNMENT = 8;

Software_Probe.prototype =
{
  //
  // header()
  //
  header: function()
  {
    return this.header_;
  },

  //
  // name()
  //
  name: function()
  {
    return this.name_.slice(0, this.name_.length - 1);
  },

  //
  //recall()
  //
  recall_with_reader: function(input)
  {
    var magic = input.read_char_array(4);

    var version = input.read_char_array(2);

    this.header_.uuid_ = input.read_uuid();

    var sec = input.read_uint32();
    var usec = input.read_uint32();
    this.header_.last_ts_.set_value(sec, usec);

    this.header_.seqnum_ = input.read_uint32();

    this.header_.state_ = input.read_uint16();

    this.header_.datasize_ = input.read_uint32();

    this.name_ = input.read_string();

    var temp = Software_Probe.MAX_ALIGNMENT - 1;
    input.offset_ = (input.offset_ + temp) & (~temp);
  },

  //
  //recall()
  //
  recall: function(packet, byte_order)
  {
    var reader = new Cdr_Reader(packet, byte_order);
    this.recall_with_reader(reader);
  }
}//end_of_Software_Probe
