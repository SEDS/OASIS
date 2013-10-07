using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using Ch.Elca.Iiop;
using OASIS;

namespace OASIS_Dashboard
{
  /// <summary>
  /// Summary description for $codebehindclassname$
  /// </summary>
  public class Probe_Schema : IHttpHandler
  {

    public void ProcessRequest (HttpContext context)
    {
      context.Response.Clear();
      context.Response.ContentType = "text/plain";

      string schema = "";
      //StringBuilder response = this.GetResponse();
      try
      {
        // Create and register new channel
        this.channel_ = new IiopClientChannel();

        ChannelServices.RegisterChannel(this.channel_, false);

        //Accessing the target object provided by TEM service
        this.tem_ =
          (TestExecutionManager)RemotingServices.Connect(typeof(TestExecutionManager),
           "corbaloc:iiop:localhost:50000/OASIS/TEM");

        DataAcquisitionController[] dacs = this.tem_.get_DACs();

        if (0 < dacs.Length)
        {
          foreach (DataAcquisitionController dac in dacs)
          {
            if (dac.name == context.Request.QueryString["DacName"])
            {
              schema = dac.get_schema(context.Request.QueryString["ProbeName"],
                                      context.Request.QueryString["EinodeName"]);

              break;
            }
          }
        }
      }
      finally
      {
        ChannelServices.UnregisterChannel(this.channel_);
      }

      context.Response.Write(schema);
      context.Response.End();
    }

    public bool IsReusable
    {
      get
      {
        return false;
      }
    }

    private IiopClientChannel channel_;
    private TestExecutionManager tem_;
  }
}
