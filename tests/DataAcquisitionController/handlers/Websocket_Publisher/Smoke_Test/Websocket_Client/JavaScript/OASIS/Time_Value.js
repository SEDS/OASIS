/**
* @class Time_Value
*
* mimics ACE_Time_Value class
*/

//
//Constructor
//
function Time_Value()
{
  this.sec_ = 0;
  this.usec_ = 0;
}

Time_Value.prototype =
{
  //
  //set_value()
  //
  set_value: function(sec,
                      usec)
  {
    this.sec_ = sec;
    this.usec_ = usec;
  }
}//end_of_Time_Value