#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>
#include <QObject>

/**
 * @brief DbManager 类 - SQLite 数据库管理单例类
 *
 * 本类封装了 Qt SQL 模块对 SQLite 数据库的常用操作，采用单例模式确保全局只有一个数据库连接。
 *
 * 主要功能：
 * - 数据库的打开与关闭
 * - 执行 SQL 语句（INSERT、UPDATE、DELETE）
 * - 查询数据（SELECT）
 * - 事务处理（开启、提交、回滚）
 * - 错误信息获取
 *
 * 使用示例：
 *   @code
 *   // 打开数据库
 *   DbManager::instance().open("my.db");
 *
 *   // 执行 SQL
 *   DbManager::instance().execute("CREATE TABLE user (id INTEGER PRIMARY KEY, name TEXT)");
 *
 *   // 查询数据
 *   QSqlQuery query = DbManager::instance().query("SELECT * FROM user");
 *   while (query.next()) {
 *       qDebug() << query.value("name").toString();
 *   }
 *
 *   // 关闭数据库
 *   DbManager::instance().close();
 *   @endcode
 */
class DbManager
{
public:
    /**
     * @brief 获取 DbManager 单例实例
     * @return DbManager& 返回单例对象的引用
     *
     * 使用静态局部变量实现线程安全的单例模式，
     * 保证整个应用程序只有一个 DbManager 实例。
     */
    static DbManager& instance();

    /**
     * @brief 打开指定路径的 SQLite 数据库
     * @param dbPath 数据库文件路径（可以是相对路径或绝对路径）
     * @return bool 打开成功返回 true，失败返回 false
     *
     * 如果数据库文件不存在，会自动创建；
     * 如果已存在，则直接打开。
     *
     * 示例：
     *   @code
     *   DbManager::instance().open("test.db");        // 相对路径，当前目录
     *   DbManager::instance().open("C:/data/test.db"); // 绝对路径
     *   @endcode
     */
    bool open(const QString& dbPath);

    /**
     * @brief 关闭当前打开的数据库连接
     *
     * 关闭后将无法执行 SQL 操作，需要重新调用 open() 打开数据库。
     */
    void close();

    /**
     * @brief 执行一条 SQL 语句（适用于 INSERT、UPDATE、DELETE 等操作）
     * @param sql 要执行的 SQL 语句字符串
     * @return bool 执行成功返回 true，失败返回 false
     *
     * 该方法自动处理 SQL 语法错误和执行错误，
     * 错误信息可通过 lastError() 方法获取。
     *
     * 示例：
     *   @code
     *   DbManager::instance().execute("INSERT INTO user (name, age) VALUES ('Tom', 20)");
     *   DbManager::instance().execute("UPDATE user SET age = 25 WHERE name = 'Tom'");
     *   DbManager::instance().execute("DELETE FROM user WHERE id = 1");
     *   @endcode
     */
    bool execute(const QString& sql);
    bool execute(QSqlQuery&query);

    /**
     * @brief 执行一条 SQL 查询语句（适用于 SELECT 操作）
     * @param sql 要执行的 SELECT 查询语句
     * @return QSqlQuery 查询结果对象
     *
     * 返回的 QSqlQuery 对象需要手动遍历获取数据。
     * 使用 query.next() 移动到下一条记录。
     *
     * 示例：
     *   @code
     *   QSqlQuery query = DbManager::instance().query("SELECT * FROM user");
     *   while (query.next()) {
     *       QString name = query.value("name").toString();
     *       int age = query.value("age").toInt();
     *       qDebug() << name << age;
     *   }
     *   @endcode
     */
    QSqlQuery query(const QString& sql);

    /**
     * @brief 开启数据库事务
     * @return bool 开启成功返回 true，失败返回 false
     *
     * 事务可以确保一组 SQL 操作要么全部成功，要么全部失败。
     * 开启事务后，需要手动调用 commit() 提交或 rollback() 回滚。
     *
     * 示例：
     *   @code
     *   DbManager::instance().transaction();
     *   DbManager::instance().execute("INSERT INTO ... ");
     *   DbManager::instance().execute("UPDATE ... ");
     *   DbManager::instance().commit(); // 或 rollback()
     *   @endcode
     */
    bool transaction();

    /**
     * @brief 提交当前事务
     * @return bool 提交成功返回 true，失败返回 false
     *
     * 提交后，事务中的所有操作才会真正写入数据库。
     */
    bool commit();

    /**
     * @brief 回滚当前事务
     * @return bool 回滚成功返回 true，失败返回 false
     *
     * 回滚将撤销事务中所有未提交的修改。
     */
    bool rollback();

    /**
     * @brief 获取最近一次操作的错误信息
     * @return QString 错误描述字符串，如果无错误则返回空字符串
     */
    QString lastError() const;

    /**
     * @brief 检查数据库是否处于打开状态
     * @return bool 打开返回 true，关闭返回 false
     */
    bool isOpen() const;

    /**
     * @brief 获取当前连接的唯一名称
     * @return QString 连接名称字符串
     *
     * 用于区分多个数据库连接，每个 DbManager 实例有独立的连接名。
     */
    QString connectionName() const;

    /**
     * @brief 获取底层的 QSqlDatabase 数据库对象
     * @return QSqlDatabase 数据库对象引用
     *
     * 高级用户可以使用此方法进行更底层的数据库操作。
     */
    QSqlDatabase database();

private:
    /**
     * @brief 私有构造函数
     *
     * 构造函数私有化，确保外界无法直接创建 DbManager 对象，
     * 只能通过 instance() 方法获取单例实例。
     */
    DbManager();

    /**
     * @brief 私有析构函数
     *
     * 析构时自动关闭数据库连接并从 Qt 数据库管理器中移除连接。
     */
    ~DbManager();

    // 禁用拷贝构造函数，防止对象被复制
    DbManager(const DbManager&) = delete;

    // 禁用赋值运算符，防止对象被赋值
    DbManager& operator=(const DbManager&) = delete;

    // 底层的 Qt SQL 数据库对象
    QSqlDatabase m_db;

    // 当前连接的名称，用于区分不同的数据库连接
    QString m_connectionName;

    // 保存最近一次错误的信息
    QString m_lastError;
};

#endif // DBMANAGER_H
