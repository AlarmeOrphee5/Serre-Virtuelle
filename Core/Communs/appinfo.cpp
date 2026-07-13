#include "appinfo.h"

#include <QtGlobal>


QString AppInfo::name()
{
    return "Serre Virtuelle";
}


QString AppInfo::version()
{
    return "0.2.5.1";
}


QString AppInfo::build()
{
    return "Preview";
}


QString AppInfo::qtVersion()
{
    return QT_VERSION_STR;
}


QString AppInfo::fullVersion()
{
    return QString("%1 v%2")
    .arg(name())
        .arg(version());
}

QString AppInfo::autheur()
{
    return "AlarmeOrphee5";
}

QString AppInfo::github()
{
    return "https://github.com/AlarmeOrphee5";
}
