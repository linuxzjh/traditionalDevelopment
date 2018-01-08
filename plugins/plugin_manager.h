#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <QObject>

class QPluginLoader;
class PluginMangerPrivate;

class PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager* instance();
    void loadAll(); //加载所有插件
    void scan(const QString& path); //扫描配置文件中所有插件元数据
    void load(const QString& path); //加载插件
    void unloadAll();   //卸载所有插件
    void unload(const QString& path); //卸载插件
    QList<QPluginLoader *> plugins(); //获取所有插件
private:
    explicit PluginManager(QObject *parent = nullptr);
    ~PluginManager();
private:
    static PluginManager *m_instance;
    PluginMangerPrivate *d;
signals:

public slots:
};

#endif // PLUGIN_MANAGER_H
