/**
* @class Linux_Processor_Probe
*
*
*/

//
//Constructor
//
function Linux_Processor_Probe ()
{
  this.nice_time_ = 0;
  this.iowait_time_ = 0;
  this.irq_time_ = 0;
  this.soft_irq_time_ = 0;
}

//
//Dynamic inheritance
//
Linux_Processor_Probe.prototype = new ProcessorProbe();

//
//recall_with_reader()
//
Linux_Processor_Probe.prototype.recall_with_reader = function(input)
{
  //calling the base class recall() to read the header
  ProcessorProbe.prototype.recall_with_reader.call(this,
                                                   input);

  //read the actual data of probe
  this.nice_time_ = input.read_uint64();
  this.iowait_time_ = input.read_uint64();
  this.irq_time_ = input.read_uint64();
  this.soft_irq_time_ = input.read_uint64();
}

//
//recall()
//
Linux_Processor_Probe.prototype.recall = function(packet, byte_order)
{
  var reader = new Cdr_Reader(packet,
                              byte_order);
  this.recall_with_reader(reader);
}
//end_of_ProcessorProbe
