/**
* @class Memory_Probe
*
*
*/

//
//Constructor
//
function Memory_Probe()
{
  this.physical_memory_avail_ = 0;
  this.physical_memory_total_ = 0;

  this.system_cache_ = 0;

  this.commit_limit_ = 0;
  this.commit_total_ = 0;

  this.virtual_total_ = 0;
  this.virtual_used_ = 0;
}

//
//Dynamic inheritance
//
Memory_Probe.prototype = new Software_Probe();

//
//recall_with_reader()
//
Memory_Probe.prototype.recall_with_reader = function(input)
{
  //calling the base class recall() to read the header
  Software_Probe.prototype.recall_with_reader.call(this,
                                                   input);

  //read the actual data of probe
  this.physical_memory_avail_ = input.read_uint64();
  this.physical_memory_total_ = input.read_uint64();

  this.system_cache_ = input.read_uint64();

  this.commit_limit_ = input.read_uint64();
  this.commit_total_ = input.read_uint64();

  this.virtual_total_ = input.read_uint64();
  this.virtual_used_ = input.read_uint64();
}

//
//recall()
//
Memory_Probe.prototype.recall = function(packet, byte_order)
{
  var reader = new Cdr_Reader(packet,
                              byte_order);
  this.recall_with_reader(reader);
}
//end_of_Memory_Probe