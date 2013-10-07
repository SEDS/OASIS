/**
* @class Windows_Memory_Probe
*
*
*/

//
//Constructor
//
function Windows_Memory_Probe()
{
  this.page_file_total_ = 0;
  this.page_file_avail_ = 0;

  this.kernel_total_ = 0;
  this.kernel_paged_ = 0;
  this.kernel_nonpaged_ = 0;

  this.page_size_ = 0;

  this.commit_peak_ = 0;
}

//
//Dynamiic Inhertence
//
Windows_Memory_Probe.prototype = new Memory_Probe();

//
//recall_with_reader()
//
Windows_Memory_Probe.prototype.recall_with_reader = function(input)
{
  //calling the base class recall() to read the header
  Memory_Probe.prototype.recall_with_reader.call(this,
                                                 input);

  //read the actual data of probe
  this.page_file_total_ = input.read_uint64();
  this.page_file_avail_ = input.read_uint64();

  this.kernel_total_ = input.read_uint64();
  this.kernel_paged_ = input.read_uint64();
  this.kernel_nonpaged_ = input.read_uint64();

  this.page_size = input.read_uint64();

  this.commit_peak_ = input.read_uint64();
}

//
//recall()
//
Windows_Memory_Probe.prototype.recall = function(packet, byte_order)
{
  var reader = new Cdr_Reader(packet,
                              byte_order);
  this.recall_with_reader(reader);
}
//end_of_Windows_Memory_Probe