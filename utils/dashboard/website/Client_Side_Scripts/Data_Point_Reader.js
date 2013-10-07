/**
* @class Probe
*
*
*/

//
//Constructor
//
function Int8_Reader()
{

}

// Here index is an object. This trick is used to make index an
// out parameter
Int8_Reader.prototype.read = function(buffer, index)
{
  var data_view = new DataView(buffer);
  return data_view.getInt8(index.value++);
}

//
//Constructor
//
function Uint8_Reader()
{
}

Uint8_Reader.read = function(buffer, index)
{
  var data_view = new DataView(buffer);
  return data_view.getUint8(index.value++);
}

// Here index is an object. This trick is used to make index an
// out parameter
Uint8_Reader.prototype.read = function(buffer, index)
{
  var data_view = new DataView(buffer);
  return data_view.getUint8(index.value++);
}

//
//Constructor
//
function Int16_Reader()
{

}

// Here index is an object. This trick is used to make index an
// out parameter
Int16_Reader.prototype.read = function(buffer, index)
{
  var data_view = new DataView(buffer);
  var temp = 2 - 1;
  index.value = (index.value + temp) & (~temp);
  var short_val = data_view.getInt16(index.value);
  index.value = index.value + 2;

  return short_val;
}

//
//Constructor
//
function Uint16_Reader()
{

}

// Here index is an object. This trick is used to make index an
// out parameter
Uint16_Reader.prototype.read = function(buffer, index)
{
  var data_view = new DataView(buffer);
  var temp = 2 - 1;
  index.value = (index.value + temp) & (~temp);
  var ushort_val = data_view.getUint16(index.value);
  index.value = index.value + 2;

  return ushort_val;
}

//
//Constructor
//
function Int32_Reader()
{

}

// Here index is an object. This trick is used to make index an
// out parameter
Int32_Reader.prototype.read = function(buffer, index)
{
  var data_view = new DataView(buffer);
  var temp = 4 - 1;
  index.value = (index.value + temp) & (~temp);
  var int_val = data_view.getInt32(index.value);
  index.value = index.value + 4;

  return int_val;
}

//
//Constructor
//
function Uint32_Reader()
{

}

// Here index is an object. This trick is used to make index an
// out parameter
Uint32_Reader.prototype.read = function(buffer, index)
{
  var data_view = new DataView(buffer);
  var temp = 4 - 1;
  index.value = (index.value + temp) & (~temp);
  var uint_val = data_view.getUint32(index.value);
  index.value = index.value + 4;

  return uint_val;
}

//
//Constructor
//
function Uint64_Reader()
{

}

// Here index is an object. This trick is used to make index an
// out parameter
Uint64_Reader.prototype.read = function(buffer, index)
{
  var data_view = new DataView(buffer);
  var temp = 8 - 1;
  index.value = (index.value + temp) & (~temp);

  var b0 = Uint8_Reader.read(buffer, index);
  var b1 = Uint8_Reader.read(buffer, index);
  var b2 = Uint8_Reader.read(buffer, index);
  var b3 = Uint8_Reader.read(buffer, index);
  var b4 = Uint8_Reader.read(buffer, index);
  var b5 = Uint8_Reader.read(buffer, index);

  // first two bits of b6 has to be 00
  var b6 = Uint8_Reader.read(buffer, index);

  // b7 has to be 00000000
  var b7 = Uint8_Reader.read(buffer, index);

  //if (this.isLittleEndian_)
  //{
    var number = ((b6 * Math.pow(2, 48)) + (b5 * Math.pow(2, 40)) + (b4 * Math.pow(2, 32)) +
                    (b3 * Math.pow(2, 24)) + (b2 * Math.pow(2, 16)) + (b1 * Math.pow(2, 8)) +
                    b0);
  //}
  //else
  //{
    // TODO : Implementation for big-endian is necessary.
    //        Logic for swiping bytes needs to be done while
    //        calculating the return value.
  //}
  if (number > 9007199254740992)
    return "NaN";

  return number;
}