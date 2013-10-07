/**
* @class ProcessorProbe
*
*
*/

//
//Constructor
//
function ProcessorProbe()
{
  this.idle_time_ = 0;
  this.system_time_ = 0;
  this.user_time_ = 0;
}

//
//Dynamic inheritance
//
ProcessorProbe.prototype = new Software_Probe();

//
//recall_with_reader()
//
ProcessorProbe.prototype.recall_with_reader = function(input)
{
  //calling the base class recall() to read the header
  Software_Probe.prototype.recall_with_reader.call(this,
                                                   input);

  //read the actual data of probe
  this.idle_time_ = input.read_uint64();
  this.system_time_ = input.read_uint64();
  this.user_time_ = input.read_uint64();
}

//
//recall()
//
ProcessorProbe.prototype.recall = function(packet, byte_order)
{
  var reader = new Cdr_Reader(packet,
                              byte_order);
  this.recall_with_reader(reader);
}
//end_of_ProcessorProbe