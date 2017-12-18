#ifndef PLUGINMANAGERPRIVATE_H
#define PLUGINMANAGERPRIVATE_H

#include <QVariant>
#include <QHash>

class QPluginLoader;

class PluginManagerPrivate
{
public:
    PluginManagerPrivate();
    bool check(const QString& path); //检测插件依赖

    QHash<QString, QVariant> m_name; //插件路径 - 名称
    QHash<QString, QVariant> m_versions; //插件路径 - 版本
    QHash<QString, QVariantList> m_dependencies; //插件路径 - 其额外依赖的插件
    QHash<QString, QPluginLoader *> m_loaders; //插件路径 - QPluginLoader实例
};

#endif // PLUGINMANAGERPRIVATE_H
