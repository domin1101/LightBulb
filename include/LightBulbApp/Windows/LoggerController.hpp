#pragma once

#ifndef _LOGGERCONTROLLER_H_
#define _LOGGERCONTROLLER_H_

// Library includes
#include <vector>
#include <memory>

// Includes
#include "LightBulbApp/Windows/AbstractSubApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class TrainingWindow;
	class TrainingPlanRepository;
	class LoggerWindow;
	class AbstractTrainingPlan;
	class AbstractWindow;
	enum LogLevel : unsigned int;
	class AbstractLogger;
	/**
	 * \brief A sup app which acts as logger.
	 * \details The app shows log messages depending on the selected LogLevel. The app uses the StorageLogger. 
	 */
	class LoggerController : public AbstractSubApp
	{
	private:
		/**
		 * \brief The corresponding window.
		 */
		LoggerWindow* window;
		/**
		 * \brief The training plan repository used to list all current training plans.
		 */
		TrainingPlanRepository* trainingPlanRepository;
		/**
		 * \brief The currently selected training plan whose log message should be shown.
		 */
		AbstractTrainingPlan* selectedTrainingPlan;
		/**
		 * \brief Contains the index of the last shown message.
		 */
		int lastLogMessageIndex;
		/**
		 * \brief Reloads the whole log.
		 */
		void reloadLog();
		/**
		 * \brief Is true when the app currently adds new messages.
		 */
		bool logMessagesAdding;
		/**
		 * \brief True of auto scrolling is enabled.
		 */
		bool autoScrolling;
	protected:
		// Inherited:
		void prepareClose() override;
	public:
		/**
		* \brief Creates the logger controller.
		* \param mainApp The main app which should manage the sub app.
		* \param trainingPlanRepository The training plan repository.
		* \param parent The parent window.
		*/
		LoggerController(AbstractMainApp& mainApp, TrainingPlanRepository& trainingPlanRepository, AbstractWindow& parent);
		/**
		 * \brief Is called after the training plan repository has changed.
		 * \param trainingPlanRepository 
		 */
		void trainingPlansChanged(TrainingPlanRepository& trainingPlanRepository);
		/**
		 * \brief Returns all current training plans.
		 * \return The vector of all training plans.
		 */
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>& getTrainingPlans() const;
		/**
		 * \brief Returns the corresponding window.
		 * \return The window.
		 */
		LoggerWindow& getWindow();
		/**
		 * \brief Sets the log level which determines which messages to show.
		 * \param level The new log level.
		 */
		void setLogLevel(int level);
		/**
		 * \brief Is called after the log has changed.
		 * \param logger The logger.
		 */
		void logChanged(AbstractLogger& logger);
		/**
		 * \brief Returns all relevant messages.
		 * \return A vector with all messages and their log levels.
		 */
		const std::vector<std::pair<LogLevel, std::string>>& getMessages() const;
		/**
		 * \brief Returns the current log level.
		 * \return The current log level.
		 */
		const LogLevel& getLogLevel() const;
		/**
		 * \brief Sets if auto scrolling should be enabled.
		 * \param newAutoScrolling The auto scrolling value.
		 */
		void setAutoScrolling(bool newAutoScrolling);
		/**
		 * \brief Returns if auto scrolling is enabled.
		 * \return True if auto scrolling is enabled.
		 */
		bool isAutoScrolling() const;
		/**
		 * \brief Returns label of the sub app.
		 * \return The label.
		 */
		static std::string getLabel();
		/**
		 * \brief Selects the 
		 * \param trainingPlanIndex 
		 */
		void selectTrainingPlan(int trainingPlanIndex);
		/**
		 * \brief Is called after new messages had been added to the output.
		 */
		void logMessagesAddingFinished();
		/**
		* \brief Locks the messages variable of the logger.
		*/
		void lockMessages();
		/**
		* \brief Unlocks the messages variable of the logger.
		*/
		void unlockMessages();
	};
}

#endif
