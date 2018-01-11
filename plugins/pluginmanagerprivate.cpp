#include "pluginmanagerprivate.h"
#include <QDebug>

PluginManagerPrivate::PluginManagerPrivate()
{

}

bool PluginManagerPrivate::check(const QString &path)
{
    bool status = true;

    foreach (QVariant item, m_dependencies.value(path)) {
        QVariantMap map = item.toMap();
        QVariant name = map.value("name");
        QVariant version = map.value("version");
        QString path = m_names.key(name);

        //检查插件是否依赖于其他插件
        //先检查插件名称
        if (!m_names.values().contains(name)) {
            qDebug() << Q_FUNC_INFO << name.toString()
                     << "for plugin" << path;
            status = false;
            continue;
        }

        //检查插件版本
        if (m_versions.value(path) != version) {
            qDebug() << Q_FUNC_INFO << " Version mismatch:"
                     << name.toString() << "version"
                     << m_versions.value(m_names.key(name)).toString()
                     << "but" << version.toString() << "required for plugin";
            status = false;
            continue;
        }
        //然后检查被依赖的插件是否依赖于另外的插件
        if (!check(path)) {
            qDebug() << Q_FUNC_INFO << "Corrupted dependency:" << name.toString()
                     << "for plugin" << path;
            status = false;
            continue;
        }
    }

    return status;
}
