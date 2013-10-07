/**
* @class Probe
*
*
*/

//
//Constructor
//
function Header()
{
  this.magic_ = 0;
  this.version_ = 0;
  this.uuid_ = new UUID();
  this.sec_ = 0;
  this.usec_ = 0;
  this.seqnum_ = 0;
  this.state_ = 0;
  this.datasize_ = 0;
  this.name_ = 0;
}

Header.MAX_ALIGNMENT = 8;

//
//
//
Header.prototype.read_header = function(packet, byte_order)
{
  var reader = new Cdr_Reader(packet, byte_order);

  this.magic_ = reader.read_char_array(4);

  this.version_ = reader.read_char_array(2);

  this.uuid_ = reader.read_uuid();

  this.sec_ = reader.read_uint32();
  this.usec_ = reader.read_uint32();

  this.seqnum_ = reader.read_uint32();

  this.state_ = reader.read_uint16();

  this.datasize_ = reader.read_uint32();

  this.name_ = reader.read_string();

  var temp = Header.MAX_ALIGNMENT - 1;
  reader.offset_ = (reader.offset_ + temp) & (~temp);

  return reader.offset_;
}

Header.prototype.name = function()
{
  return this.name_.slice(0, this.name_.length - 1);
}