/**
* @class Probe
*
*
*/

//
//Constructor
//
function Probe(xml_dom_root,dac_einode_probe,divElement,ws)
{
  // readers created based on data type of data point
  // in schema.
  this.datapointreaders = new Array();

  //data points name as per schema.
  this.datapoints = new Array();

  // root of XML DOM.
  this.root = xml_dom_root;

  // This variable represent table for this probe.
  this.probeTable = 0;

  //Index to keep track where to read in buffer
  this.index = {};

  // div to display data
  this.appBodyDiv = divElement;

  // This div will be child app body div and will
  // hold probe data table and other probe specific
  // controls
  this.probeDiv = 0;

  this.dacName = dac_einode_probe[0];

  this.einodeName = dac_einode_probe[1];

  this.name = dac_einode_probe[2];

  // Data_Point_Reader
  this.data_point_reader_producer = new Data_Point_Reader_Factory()

  // draws basic structure of probe table.
  this.draw_table_header(dac_einode_probe);
}

//
//draw_table_header()
//
// This function is there to create table tag and set the
// table header. We can't do that in other draw () because
// its recursive in nature.
// NOTE: There might be other way to handle this situation
//       but I have other big issues right now (6/5/2012).
//
Probe.prototype.draw_table_header = function(id)
{
  // Here we need to figure out the position of table.
  this.probeDiv = document.createElement('div');
  Probe.ProbeDiv = this.probeDiv;
  var divId = id[0] + " " + id[1] + " " + id[2] + " " + "probeDiv";
  this.probeDiv.setAttribute('id', divId);
  this.probeDiv.setAttribute('style', 'float:left');
  this.probeDiv.setAttribute('border', '1');

  this.probeTable = document.createElement('table');
  var table_id = id[0] + " " + id[1] + " " + id[2] + " " + "probeTable";
  this.probeTable.setAttribute('id', table_id);
  this.probeTable.setAttribute('border', '1');
  header = document.createElement('th');
  header.setAttribute('colspan', '2');
  header.appendChild(document.createTextNode(this.name));
  this.probeTable.appendChild(header);
}

//
//draw ()
//
//This function is responsible for drawing table and
//creating redears for each datapoint
//
Probe.prototype.buildTable = function(dom_node)
{
  // Here dom_node is first complexType in whole DOM. We
  // start processing first compexType by traversing all
  // its childNodes.
  var children = dom_node.childNodes;
  for (k = 0; k < children.length; k++)
  {
    if (children[k].localName == "complexType" || children[k].localName == "sequence")
    {
      if (children[k].childNodes[0] != undefined && children[k].childNodes[0].localName == "complexContent")
      {
        for (i = 0; i < children[k].childNodes[0].childNodes.length; i++)
        {
          // This if check is there to see the complexType referes
          // another complexType as its base class. If yes then we
          // have to locate that complex type in DOM and process that
          // first. Its a recursive approach.
          if (children[k].childNodes[0].childNodes[i].localName == "extension")
          {
            // Here we store the base type that is referred so we
            // can indentify base complex type in DOM.
            var base_name = children[k].childNodes[0].childNodes[i].getAttribute("base");

            // Here we have to traverse all children of DOM root because
            // We don't know exact location of required complexType.
            var root_children = this.root.childNodes;
            for (j = 0; j < root_children.length; j++)
            {
              if (root_children[j].localName == "complexType")
              {
                if (root_children[j].getAttribute("name") == base_name)
                {
                  this.buildTable(root_children[j]);
                  this.buildTable(children[k].childNodes[0].childNodes[i]);
                }
              }
            }
          }
        }
      }
      else if (children[0].localName == "sequence")
      {
        // Here we get all the childeren of sequence. This elements
        // array contains all the data points we need to draw in
        // table. We also create reader based on type attribute of
        // element tag.
        var elements = children[0].childNodes;

        // This checck is there to avoid script going into infinity
        // loop which happens because of recursive nature og this function.
        // If concrete type probe doesnt have any extra element than bast
        // type then its sequence will be empty and we will know for sure
        // our schema traverssal is complete.
        if (0 >= elements.length || elements == undefined)
          return;

        for (j = 0; j < elements.length; j++)
        {
          row = document.createElement('tr');
          element_name = elements[j].getAttribute("name");

          left_cell = document.createElement('td');
          left_cell.appendChild(document.createTextNode(element_name));
          row.appendChild(left_cell);

          right_cell = document.createElement('td');
          var cell_id = this.einodeName + " " + this.name + " " + element_name;
          this.datapoints.push(cell_id);
          right_cell.setAttribute('id', cell_id);
          row.appendChild(right_cell);

          this.probeTable.appendChild(row);
          element_type = elements[j].getAttribute("type");
          this.datapointreaders.push(this.data_point_reader_producer.get_reader(element_type));
        }
      }
    }
  }
  this.drawTable();
}

Probe.prototype.drawTable = function()
{
  this.probeDiv.innerHTML = "";
  this.probeDiv.appendChild(this.probeTable);

  var lbl = document.createElement('lable');
  lbl.appendChild(document.createTextNode("Enter Heartz : "));
  this.probeDiv.appendChild(lbl);

  var txt = document.createElement('input')
  txt.setAttribute('type', 'text');
  var txtId = this.dacName + " " + this.einodeName + " " + this.name + " " + "hertzText";
  txt.setAttribute('id', txtId);
  this.probeDiv.appendChild(txt);

  var btnHertz = document.createElement('input');
  btnHertz.setAttribute('type', 'button');
  var btnId = this.dacName + " " + this.einodeName + " " + this.name + " " + "hertzButton";
  btnHertz.setAttribute('id', btnId);
  btnHertz.setAttribute('value', "Change");
  btnHertz.setAttribute('onclick', 'changeHeartz(event)');
  this.probeDiv.appendChild(btnHertz);

  var breakline = document.createElement('br');
  this.probeDiv.appendChild(breakline);

  var btnUnregister = document.createElement('input');
  btnUnregister.setAttribute('type', 'button');
  btnId = this.dacName + " " + this.einodeName + " " + this.name + " " + "unregiaterButton";
  btnUnregister.setAttribute('id', btnId);
  btnUnregister.setAttribute('value', "Unregister");
  btnUnregister.setAttribute('onclick', 'unregister(event)');
  this.probeDiv.appendChild(btnUnregister);

  this.appBodyDiv.appendChild(this.probeDiv);
}
//
//refresh ()
//
//This function is responsible for refreshing values
//of datapoints when new data is available.
//
Probe.prototype.refresh = function(buffer, start_point)
{
  this.index.value = start_point;
  for (i = 0; i < this.datapoints.length; i++)
  {
    document.getElementById(this.datapoints[i]).innerHTML =
                      this.datapointreaders[i].read(buffer, this.index);
  }
}
