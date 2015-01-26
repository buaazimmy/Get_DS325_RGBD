#include <stdlib.h>
#include <iostream>

#include <DepthSense.hxx>
 
int aaaa;
using namespace std;
using namespace DepthSense;

static void error (const char* message)
{
    cerr << message << endl;
    exit(1);
}

static ColorNode getFirstAvailableColorNode (Context depthsense)
{
  // obtain the list of devices attached to the host
  vector<Device> devices = depthsense.getDevices();

  for (vector<Device>::const_iterator iter = devices.begin(); iter != devices.end(); iter++)
  {
      Device device = *iter;

      // obtain the list of nodes of the current device
      vector<Node> nodes = device.getNodes();

      for (vector<Node>::const_iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++)
      {
          Node node = *nodeIter;

          // if the node is a DepthSense::ColorNode, return it
          ColorNode colorNode = node.as<ColorNode>();
          if (colorNode.isSet())
              return colorNode;
      }
  }

  // return an unset color node
  return ColorNode();
}

static void onNewColorSample (ColorNode obj, ColorNode::NewSampleReceivedData data)
{
    cout << "New color sample received (timeOfCapture=" << data.timeOfCapture << ")" << endl;
}

int main (int argc, char** argv)
{
    // create a connection to the DepthSense server at localhost
    Context depthsense = Context::create();

    // get the first available color sensor
    ColorNode colorNode = getFirstAvailableColorNode(depthsense);
  
    // if no color node was found, fail
    if (! colorNode.isSet())
        error("no color node found");

    // enable the capture of the color map
    colorNode.setEnableColorMap(true);

    // connect a callback to the newSampleReceived event of the color node
    colorNode.newSampleReceivedEvent().connect(onNewColorSample);

    // add the color node to the list of nodes that will be streamed
    depthsense.registerNode(colorNode);

    // start streaming
    depthsense.startNodes();

    // start the DepthSense main event loop
    depthsense.run();
}
