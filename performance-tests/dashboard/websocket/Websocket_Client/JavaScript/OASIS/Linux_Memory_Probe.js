/**
* @class Linux_Memory_Probe
*
*
*/

//
//Constructor
//
function Linux_Memory_Probe()
{
  this.buffers_ = 0;
  this.swap_cache_ = 0;

  this.inactive_ = 0;
  this.active_ = 0;

  this.high_total_ = 0;
  this.high_free_ = 0;

  this.low_total_ = 0;
  this.low_free_ = 0;

  this.swap_total_ = 0;
  this.swap_free_ = 0;

  this.dirty_ = 0;
  this.write_back_ = 0;

  this.virtual_chunk_ = 0;
}

//
//Dynamiic Inhertence
//
Linux_Memory_Probe.prototype = new Memory_Probe();

//
//recall_with_reader()
//
Linux_Memory_Probe.prototype.recall_with_reader = function(input)
{
  //calling the base class recall() to read the header
  Memory_Probe.prototype.recall_with_reader.call(this,
                                                 input);

  //read the actual data of probe
  this.buffers_ = input.read_uint64();
  this.swap_cache_ = input.read_uint64();

  this.inactive_ = input.read_uint64();
  this.active_ = input.read_uint64();

  this.high_total_ = input.read_uint64();
  this.high_free_ = input.read_uint64();

  this.low_total_ = input.read_uint64();
  this.low_free_ = input.read_uint64();

  this.swap_total_ = input.read_uint64();
  this.swap_free_ = input.read_uint64();

  this.dirty_ = input.read_uint64();
  this.write_back_ = input.read_uint64();

  this.virtual_chunk_ = input.read_uint64();
}

//
//recall()
//
Linux_Memory_Probe.prototype.recall = function(packet, byte_order)
{
  var reader = new Cdr_Reader(packet,
                              byte_order);
  this.recall_with_reader(reader);
}
//end_of_Windows_Memory_Probe