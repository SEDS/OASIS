using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

using System.Text;
using System.Web.Script.Serialization;
using System.Xml;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using Ch.Elca.Iiop;
using OASIS;

namespace OASIS_Dashboard.Scripts
{
  /// <summary>
  /// Summary description for $codebehindclassname$
  /// </summary>
  public class Menu_Data : IHttpHandler
  {
    public void ProcessRequest (HttpContext context)
    {
      Menu menu = new Menu();

      context.Response.Clear();
      context.Response.ContentType = "text/plain";

      //StringBuilder response = this.GetResponse();
      try
      {
        // Create and register new channel
        this.channel_ = new IiopClientChannel();

        ChannelServices.RegisterChannel(this.channel_, false);

        //Accessing the target object provided by TEM service
        this.tem_ =
          (TestExecutionManager)RemotingServices.Connect(typeof(TestExecutionManager),
                                                         context.Request.QueryString["temLocation"]);

        DataAcquisitionController[] dacs = this.tem_.get_DACs();

        if (0 < dacs.Length)
        {
          menu.Dacs = new List<DAC>();

          foreach (DataAcquisitionController dac in dacs)
          {
            DAC dac_element = new DAC();
            dac_element.Name = dac.name;
            dac_element.Probes = new List<Probe>();
            this.probes_ = dac.get_probe_instances();
            if (0 < this.probes_.Length)
            {
              foreach (ProbeInstance probe in this.probes_)
              {
                Probe probe_element = new Probe();
                probe_element.Name = probe.inst_name;
                probe_element.Einode_Name = probe.einode_name;
                probe_element.Uuid = probe.inst_uuid;
                probe_element.Type_Name = probe.inst_type_name;

                dac_element.Probes.Add(probe_element);
              }
            }
            menu.Dacs.Add(dac_element);
          }
        }
      }
      finally
      {
        ChannelServices.UnregisterChannel(this.channel_);
      }

      StringBuilder response = new StringBuilder();
      JavaScriptSerializer ser = new JavaScriptSerializer();
      ser.Serialize(menu,response);
      context.Response.Write(response.ToString());

      context.Response.End();
    }

    public bool IsReusable
    {
      get
      {
        return false;
      }
    }

    private ProbeInstance[] probes_;
    private IiopClientChannel channel_;
    private TestExecutionManager tem_;
  }
}
