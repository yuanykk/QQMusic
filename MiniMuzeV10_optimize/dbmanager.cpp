#include "dbmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QDir>

/**
 * @brief 构造函数 - 初始化数据库连接
 *
 * 为每个 DbManager 实例生成唯一的连接名称，使用 Qt 的数据库连接管理机制。
 * 连接名称格式为 "DbManager_Connection_0xXXXX"，其中 XXXX 是对象的内存地址。
 *
 * 这样设计的好处：
 * 1. 避免与其他数据库连接冲突
 * 2. 可以在多线程环境下使用不同的连接
 * 3. Qt 要求每个数据库连接有唯一的名称
 */
DbManager::DbManager()
    // 使用对象自身的内存地址作为连接名称的一部分，确保唯一性
    : m_connectionName(QString("DbManager_Connection_%1").arg(reinterpret_cast<quint64>(this)))
{
}

/**
 * @brief 析构函数 - 清理数据库资源
 *
 * 在对象销毁时自动执行以下清理操作：
 * 1. 如果数据库处于打开状态，则关闭数据库连接
 * 2. 从 Qt 的全局数据库连接池中移除此连接
 *
 * 这确保了程序退出时数据库资源被正确释放，不会造成资源泄漏。
 */
DbManager::~DbManager()
{
    // 检查数据库是否处于打开状态，如果是则关闭
    if (m_db.isOpen()) {
        m_db.close();
    }

    // 从 Qt SQL 数据库管理器中移除此连接
    // 必须调用此方法，否则会留下"僵尸连接"
    QSqlDatabase::removeDatabase(m_connectionName);
}

/**
 * @brief 获取单例实例
 *
 * 使用 C++11 静态局部变量特性实现线程安全的单例模式。
 * 静态局部变量在首次调用时初始化，且只初始化一次。
 *
 * @return DbManager& 返回对唯一实例的引用
 *
 * Qt 的静态局部变量初始化是线程安全的，
 * 因此在多线程环境下也能保证只有一个实例存在。
 */
DbManager& DbManager::instance()
{
    // C++11 保证静态局部变量的初始化是线程安全的
    // 第一次调用时创建实例，后续调用返回同一实例
    static DbManager instance;
    return instance;
}

/**
 * @brief 获取当前连接的名称
 *
 * @return QString 连接名称字符串
 *
 * 连接名称在构造时生成，用于在 Qt 数据库系统中唯一标识此连接。
 * 主要用于调试和日志记录。
 */
QString DbManager::connectionName() const
{
    return m_connectionName;
}

/**
 * @brief 获取底层的 QSqlDatabase 对象
 *
 * @return QSqlDatabase 数据库对象
 *
 * 高级用户可以使用返回的 QSqlDatabase 对象进行更底层的操作，
 * 如设置连接参数、获取表列表等。
 */
QSqlDatabase DbManager::database()
{
    return m_db;
}

/**
 * @brief 检查数据库是否已打开
 *
 * @return bool 如果数据库处于打开状态返回 true，否则返回 false
 *
 * 建议在执行 SQL 操作前先调用此方法检查数据库状态。
 */
bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

/**
 * @brief 打开指定路径的 SQLite 数据库
 *
 * 本方法完成以下操作：
 * 1. 如果已有连接打开，先关闭该连接
 * 2. 创建 QSQLITE 类型的数据库驱动
 * 3. 设置数据库文件路径
 * 4. 尝试打开数据库连接
 *
 * @param dbPath 数据库文件的路径（支持相对路径和绝对路径）
 * @return bool 打开成功返回 true，失败返回 false
 *
 * SQLite 数据库特点：
 * - 如果指定路径的文件不存在，会自动创建一个新的空数据库
 * - SQLite 是文件数据库，整个数据库存储在一个 .db 文件中
 *
 * 示例：
 *   @code
 *   // 打开当前目录下的数据库
 *   DbManager::instance().open("myapp.db");
 *
 *   // 打开指定目录的数据库
 *   DbManager::instance().open("C:/data/myapp.db");
 *   @endcode
 */
bool DbManager::open(const QString& dbPath)
{
    // 第一步：如果数据库已经打开，先关闭它
    // 这样可以避免重复打开或连接冲突
    if (m_db.isOpen()) {
        m_db.close();
    }

    // 第二步：添加 SQLite 数据库驱动
    // QSQLITE 是 Qt 内置的 SQLite 驱动，无需额外配置
    // 第二个参数是连接名称，必须唯一
    m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), m_connectionName);

    // 第三步：设置数据库文件路径
    // SQLite 将整个数据库存储在一个文件中
    m_db.setDatabaseName(dbPath);

    // 第四步：尝试打开数据库
    if (!m_db.open()) {
        // 打开失败，记录错误信息
        m_lastError = m_db.lastError().text();
        qWarning() << "Failed to open database:" << m_lastError;
        return false;
    }

    return true;
}

/**
 * @brief 关闭数据库连接
 *
 * 关闭后，所有未提交的事务都会被回滚。
 * 关闭后将无法执行 SQL 操作，如需继续使用需要重新调用 open()。
 *
 * 注意：关闭数据库不会删除数据库文件，数据会持久保存在磁盘上。
 */
void DbManager::close()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

/**
 * @brief 执行一条 SQL 语句（INSERT、UPDATE、DELETE 等）
 *
 * 适用于不需要返回结果的 SQL 操作。
 * 如果 SQL 执行失败，会自动记录错误信息，可通过 lastError() 获取。
 *
 * @param sql 要执行的 SQL 语句字符串
 * @return bool 执行成功返回 true，失败返回 false
 *
 * 使用示例：
 *   @code
 *   // 插入数据
 *   DbManager::instance().execute("INSERT INTO user (name, age) VALUES ('Tom', 25)");
 *
 *   // 更新数据
 *   DbManager::instance().execute("UPDATE user SET age = 30 WHERE name = 'Tom'");
 *
 *   // 删除数据
 *   DbManager::instance().execute("DELETE FROM user WHERE id = 1");
 *
 *   // 创建表
 *   DbManager::instance().execute("CREATE TABLE IF NOT EXISTS user ("
 *                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
 *                                 "name TEXT NOT NULL)");
 *   @endcode
 */
bool DbManager::execute(const QString& sql)
{
    // 检查数据库是否已打开，未打开则无法执行 SQL
    if (!m_db.isOpen()) {
        m_lastError = QStringLiteral("Database is not open");
        return false;
    }

    // 创建查询对象，绑定到当前数据库连接
    QSqlQuery query(m_db);

    // 执行 SQL 语句
    // exec() 返回 true 表示 SQL 被成功执行（但不代表有结果集）
    // 注意：即使 SQL 语法正确，执行失败（如约束冲突）也会返回 false
    if (!query.exec(sql)) {
        // 执行失败，记录错误信息和 SQL 语句，便于调试
        m_lastError = query.lastError().text();
        qWarning() << "Execute failed:" << m_lastError << "SQL:" << sql;
        return false;
    }

    return true;
}


bool DbManager::execute(QSqlQuery &query)
{
    // 检查数据库是否已打开，未打开则无法执行 SQL
    if (!m_db.isOpen()) {
        m_lastError = QStringLiteral("Database is not open");
        return false;
    }
    // 执行 SQL 语句
    // exec() 返回 true 表示 SQL 被成功执行（但不代表有结果集）
    // 注意：即使 SQL 语法正确，执行失败（如约束冲突）也会返回 false
    if (!query.exec()) {
        // 执行失败，记录错误信息和 SQL 语句，便于调试
        m_lastError = query.lastError().text();
        qWarning() << "Execute failed:" << m_lastError << "SQL:";
        return false;
    }

    return true;
}

/**
 * @brief 执行一条 SQL 查询语句（SELECT）
 *
 * 用于从数据库中查询数据，返回 QSqlQuery 对象。
 * 需要手动遍历查询结果。
 *
 * @param sql SELECT 查询语句
 * @return QSqlQuery 查询结果对象
 *
 * 使用示例：
 *   @code
 *   // 查询所有记录
 *   QSqlQuery query = DbManager::instance().query("SELECT * FROM user");
 *
 *   // 遍历结果集
 *   while (query.next()) {
 *       // 按列名获取值
 *       int id = query.value("id").toInt();
 *       QString name = query.value("name").toString();
 *       int age = query.value("age").toInt();
 *
 *       // 或者按列索引获取值（从 0 开始）
 *       // int id = query.value(0).toInt();
 *       // QString name = query.value(1).toString();
 *
 *       qDebug() << id << name << age;
 *   }
 *
 *   // 查询单条记录
 *   QSqlQuery query = DbManager::instance().query("SELECT COUNT(*) FROM user");
 *   if (query.next()) {
 *       int count = query.value(0).toInt();
 *   }
 *   @endcode
 *
 * QSqlQuery 遍历说明：
 * - 初始时，query 指向结果集之前的位置（before the first）
 * - 第一次调用 next() 会移动到第一条记录
 * - next() 返回 true 表示还有下一条记录，返回 false 表示已遍历完毕
 * - 也可以使用 previous()、first()、last()、seek() 等方法移动指针
 */
QSqlQuery DbManager::query(const QString& sql)
{
    // 创建查询对象，绑定到当前数据库连接
    QSqlQuery query(m_db);

    // 检查数据库是否已打开
    if (!m_db.isOpen()) {
        m_lastError = QStringLiteral("Database is not open");
        qWarning() << m_lastError;
        return query;
    }

    // 执行 SQL 查询
    if (!query.exec(sql)) {
        // 查询失败，记录错误信息
        m_lastError = query.lastError().text();
        qWarning() << "Query failed:" << m_lastError << "SQL:" << sql;
    }

    // 返回查询对象（即使失败也返回，调用者可以检查 isValid() 等状态）
    return query;
}

/**
 * @brief 开启数据库事务
 *
 * 事务用于将多个 SQL 操作组合成一个原子操作：
 * - 要么全部成功执行并提交
 * - 要么任何一步失败则全部回滚
 *
 * 事务的典型使用场景：
 * 1. 批量插入数据（一条失败则全部回滚）
 * 2. 转账操作（扣款和存款必须同时成功）
 * 3. 需要保持数据一致性的复杂操作
 *
 * @return bool 开启成功返回 true，失败返回 false
 *
 * 使用示例：
 *   @code
 *   // 开启事务
 *   if (!DbManager::instance().transaction()) {
 *       qDebug() << "开启事务失败";
 *       return;
 *   }
 *
 *   bool allSuccess = true;
 *   allSuccess &= DbManager::instance().execute("INSERT INTO account ...");
 *   allSuccess &= DbManager::instance().execute("UPDATE account ...");
 *
 *   if (allSuccess) {
 *       DbManager::instance().commit();  // 提交事务
 *   } else {
 *       DbManager::instance().rollback(); // 回滚事务
 *   }
 *   @endcode
 *
 * 注意：
 * - 开启事务后必须显式调用 commit() 或 rollback()
 * - 未提交的事务在连接关闭时会自动回滚
 * - SQLite 默认使用 DEFERRED 事务模式
 */
bool DbManager::transaction()
{
    // 检查数据库是否已打开
    if (!m_db.isOpen()) {
        m_lastError = QStringLiteral("Database is not open");
        return false;
    }

    // 调用底层 QSqlDatabase 的 transaction() 方法开启事务
    return m_db.transaction();
}

/**
 * @brief 提交当前事务
 *
 * 将事务中所有未提交的修改永久写入数据库。
 * 提交后，事务结束，数据修改生效。
 *
 * @return bool 提交成功返回 true，失败返回 false
 *
 * 注意：提交成功后，之前的 transaction() 调用就完成了，
 * 如果还需要事务操作，需要重新调用 transaction()。
 */
bool DbManager::commit()
{
    // 检查数据库是否已打开
    if (!m_db.isOpen()) {
        m_lastError = QStringLiteral("Database is not open");
        return false;
    }

    // 调用底层 QSqlDatabase 的 commit() 方法提交事务
    return m_db.commit();
}

/**
 * @brief 回滚当前事务
 *
 * 撤销事务中所有未提交的修改，恢复到事务开始前的状态。
 *
 * @return bool 回滚成功返回 true，失败返回 false
 *
 * 回滚的典型场景：
 * 1. 事务中的任何一步 SQL 执行失败
 * 2. 用户取消操作
 * 3. 程序发生异常
 */
bool DbManager::rollback()
{
    // 检查数据库是否已打开
    if (!m_db.isOpen()) {
        m_lastError = QStringLiteral("Database is not open");
        return false;
    }

    // 调用底层 QSqlDatabase 的 rollback() 方法回滚事务
    return m_db.rollback();
}

/**
 * @brief 获取最近一次错误信息
 *
 * 当 execute() 或 query() 等方法返回 false 时，
 * 可以通过此方法获取详细的错误描述。
 *
 * @return QString 错误信息字符串，无错误时返回空字符串
 *
 * 注意：错误信息会在下次调用任何 SQL 方法时被覆盖。
 */
QString DbManager::lastError() const
{
    return m_lastError;
}
