#pragma once

#ifndef _ABSTRACTLINEARALGEBRAUSER_H_
#define _ABSTRACTLINEARALGEBRAUSER_H_

// Include

// Library Includes

namespace LightBulb
{
	enum CalculatorType : unsigned int;
	/**
	 * \brief Describes a class which uses linear algebra objects.
	 * \details This class helps to set determine the current calculator type.
	 */
	class AbstractLinearAlgebraUser
	{
	protected:
		/**
		 * \brief The random generator which is used.
		 * \note Before the random generator can be used, setRandomGenerator() should be called.
		 */
		CalculatorType calculatorType;
	public:
		virtual ~AbstractLinearAlgebraUser() {};
		/**
		 * \brief Creates an AbstractRandomGeneratorUser
		 */
		AbstractLinearAlgebraUser();
		/**
		 * \brief Sets the random generator which should be used.
		 * \param calculatorType The random generator.
		 */
		virtual void setCalculatorType(const CalculatorType& calculatorType);
		/**
		* \brief Sets the random generator which should be used.
		* \param calculatorType_ The random generator.
		*/
		bool isCalculatorType(const CalculatorType& calculatorType_) const;
		/**
		 * \brief Returns the currently used random generator.
		 * \return The random generator.
		 */
		const CalculatorType& getCalculatorType() const;
	};
}

#endif
