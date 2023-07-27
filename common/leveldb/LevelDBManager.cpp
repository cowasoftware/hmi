#include "LevelDBManager.h"
#include "leveldb/db.h"
#include <mutex>
#include <QDebug>
#include <iostream>

#define LOGGER GetLogMgr().getLogger()

LevelDBManager::LevelDBManager():
m_defaultDBFile(nullptr)
{

}

inline CLogMgr& LevelDBManager::GetLogMgr() {
  static CLogMgr my_logger("MAPP", "MCON", E_FUNC_LINE, DLT);
  return my_logger;
}

LevelDBManager& LevelDBManager::instance()
{
	static LevelDBManager s_levelDBManager;
	return s_levelDBManager;
}

void LevelDBManager::openDBFile(const std::string& path, int32_t fileId)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (fileId == 0 && m_defaultDBFile != nullptr)
	{
		return;
	}

	if (fileId != 0 && (m_dbFile.find(fileId) != m_dbFile.end()))
	{
		return;
	}

	leveldb::DB* dbFile = nullptr;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, path, &dbFile);
	if (!status.ok() || dbFile == nullptr)
	{
		LOGGER->Cowa_Warn("openDBFile error = %s, dbFile = %p\n", status.ToString().c_str(), dbFile);
		return;
    }
	if (fileId == 0)
	{
		m_defaultDBFile = dbFile;
		return;
	}
	
	m_dbFile[fileId] = dbFile;
}

void LevelDBManager::setConfig(const std::string& key, const std::string& value, int32_t fileId)
{
	leveldb::DB* dbFile = findDBFile(fileId);
	if (dbFile == nullptr)
	{
		// LOGGER->Cowa_Warn("setConfig error, dbFile is null.\n");
		return;
	}

	leveldb::Status status = dbFile->Put(leveldb::WriteOptions(), key, value);
    if (!status.ok())
	{
		LOGGER->Cowa_Warn("setConfig error = %s\n", status.ToString().c_str());
		return;
    }
	//LOGGER->Cowa_Info("setConfig status = %s\n", status.ToString().c_str());
}

// void LevelDBManager::slotSetConfig(QString key, QString value, int fileId) {
// 	std::string strKey = key.toStdString();
// 	std::string strValue = value.toStdString();
// 	printf("slotSetConfig, strKey = %s\n", strKey.c_str());
// 	printf("slotSetConfig, strValue = %s\n", strValue.c_str());
// 	setConfig(strKey, strValue, fileId);
// }

bool LevelDBManager::getConfig(const std::string& key, std::string& value, int32_t fileId)
{
	leveldb::DB* dbFile = findDBFile(fileId);
	if (dbFile == nullptr)
	{
		// LOGGER->Cowa_Warn("getConfig error, dbFile is null.\n");
		return false;
	}

	leveldb::Status status = dbFile->Get(leveldb::ReadOptions(), key, &value);
	if (!status.ok())
	{
		LOGGER->Cowa_Warn("getConfig error, status is not ok.\n");
		return false;
    }
	//LOGGER->Cowa_Info("getConfig success, status is ok.\n");
	return true;
}

// bool LevelDBManager::slotGetConfig(QString key, QString value, int fileId)
// {
// 	std::string strKey = key.toStdString();
// 	std::string strValue = value.toStdString();
// 	printf("slotGetConfig, strKey = %s\n", strKey.c_str());
// 	bool result = getConfig(strKey, strValue, fileId);
// 	printf("slotGetConfig, strValue = %s\n", strValue.c_str());
// 	std::cout<<"slotGetConfig: result = "<<result<<std::endl;
// 	return result;
// }

void LevelDBManager::findConfig(const std::string& key, const std::function<void(const std::string&, const std::string&)>& findConfigFun, int32_t fileId)
{
	leveldb::DB* dbFile = findDBFile(fileId);
	if (dbFile == nullptr)
	{
		return;
	}

	leveldb::Iterator* it = dbFile->NewIterator(leveldb::ReadOptions());
	if (it == nullptr)
	{
		return;
	}

	for (it->SeekToFirst(); it->Valid(); it->Next())
	{
		leveldb::Status status = it->status();
		if (!status.ok())
		{
			LOGGER->Cowa_Warn("findConfig error = %s\n", status.ToString().c_str());
		}
		else
		{
			const std::string&& keyString = it->key().ToString();
			if (keyString.find(key) != std::string::npos)
			{
				findConfigFun(keyString, it->value().ToString());
			}
		}
	}
	delete it;
}

void LevelDBManager::deleteConfig(const std::string& key, int32_t fileId)
{
	leveldb::DB* dbFile = findDBFile(fileId);
	if (dbFile == nullptr)
	{
		return;
	}

	leveldb::Status status = dbFile->Delete(leveldb::WriteOptions(), key);
	if (!status.ok())
	{
		LOGGER->Cowa_Warn("deleteConfig error = %s\n", status.ToString().c_str());
		return;
    }
}

void LevelDBManager::closeDBFile(int32_t fileId)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (fileId == 0 && m_defaultDBFile == nullptr)
	{
		return;
	}

	auto it = m_dbFile.find(fileId);
	if (fileId != 0 && (it == m_dbFile.end()))
	{
		return;
	}

	if (fileId == 0)
	{
		delete m_defaultDBFile;
		m_defaultDBFile = nullptr;
		return;
	}

	delete it->second;
	m_dbFile.erase(it);
}

leveldb::DB* LevelDBManager::findDBFile(int32_t fileId)
{
	leveldb::DB* dbFile = nullptr;
	if (fileId == 0)
	{
		dbFile = m_defaultDBFile;
	}
	else
	{
		auto it = m_dbFile.find(fileId);
		if (it == m_dbFile.end())
		{
			return nullptr;
		}
		dbFile = it->second;
	}
	return dbFile;
}