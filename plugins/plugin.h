#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>

#define PluginInterface_iid "com.Animation.PluginInterface"
/**
  *创建一个插件接口类，其他的插件均继承于它，该插件必须为一个纯虚函数
*/
class Plugin : public QObject
{
    Q_OBJECT
public:
    Plugin() {}
    virtual ~Plugin() {}
//    virtual QString toolName() const = 0;
};

Q_DECLARE_INTERFACE(Plugin, PluginInterface_iid)    //将 Plugin接口与唯一标识符一起公开

#endif // PLUGIN_H
