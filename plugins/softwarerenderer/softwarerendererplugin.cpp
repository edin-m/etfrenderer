#include "softwarerendererplugin.h"

SoftwareRendererPlugin::SoftwareRendererPlugin()
{
    m_renderer = new SoftwareRenderer;
}

SoftwareRendererPlugin::~SoftwareRendererPlugin()
{
    delete m_renderer;
}
