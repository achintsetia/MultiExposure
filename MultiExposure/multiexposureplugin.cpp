#include "multiexposure.h"

#include <QtCore/QtPlugin>
#include "multiexposureplugin.h"


MultiExposurePlugin::MultiExposurePlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void MultiExposurePlugin::initialize(QDesignerFormEditorInterface */*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool MultiExposurePlugin::isInitialized() const
{
	return initialized;
}

QWidget *MultiExposurePlugin::createWidget(QWidget *parent)
{
	return new MultiExposure(parent);
}

QString MultiExposurePlugin::name() const
{
	return "MultiExposure";
}

QString MultiExposurePlugin::group() const
{
	return "My Plugins";
}

QIcon MultiExposurePlugin::icon() const
{
	return QIcon();
}

QString MultiExposurePlugin::toolTip() const
{
	return QString();
}

QString MultiExposurePlugin::whatsThis() const
{
	return QString();
}

bool MultiExposurePlugin::isContainer() const
{
	return false;
}

QString MultiExposurePlugin::domXml() const
{
	return "<widget class=\"MultiExposure\" name=\"multiExposure\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>100</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString MultiExposurePlugin::includeFile() const
{
	return "multiexposure.h";
}

Q_EXPORT_PLUGIN2(multiexposure, MultiExposurePlugin)
