#pragma once

#ifndef _STORAGELOGGER_H_
#define _STORAGELOGGER_H_

// Library Includes
#include <vector>

// Includes
#include "LightBulb/Logging/AbstractLogger.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a logger which stores all messages.
	 * \note Does not need a current log level, because ALL messages are stored.
	 */
	class StorageLogger : public AbstractLogger
	{
		template <class Archive>
		friend void serialize(Archive& archive, StorageLogger& storageLogger);
	protected:
		/**
		 * \brief The storage.
		 * \details Loglevel and message text of every message.
		 */
		std::vector<std::pair<LogLevel, std::string>> messages;
		/**
		 * \brief A mutex to make messages thread safe.
		 */
		std::mutex messagesMutex;
	public:
		/**
		 * \brief Creates the logger
		 */
		StorageLogger();
		/**
		 * \brief Returns all messages.
		 * \return All messages.
		 */
		const std::vector<std::pair<LogLevel, std::string>>& getMessages() const;
		/**
		 * \brief Locks the access to the messages storages.
		 */
		void lockMessages();
		/**
		 * \brief Unlocks the access to the messages storages.
		 */
		void unlockMessages();
		// Inherited:
		void log(const std::string& message, const LogLevel& level) override;
	};
}

#include "LightBulb/IO/StorageLoggerIO.hpp"

#endif

