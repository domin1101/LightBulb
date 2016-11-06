
#pragma once

#ifndef _ABSTRACTRANDOMGENERATOR_H_
#define _ABSTRACTRANDOMGENERATOR_H_

// Include

// Library Includes
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a generator of random numbers.
	 */
	class AbstractRandomGenerator
	{
	private:
	protected:
		int seed;
		int getRandomSeed();
		virtual void reset() = 0;
	public:
		virtual ~AbstractRandomGenerator() {};
		AbstractRandomGenerator(int seed_);
		/**
		 * \brief Generates a random double between [0, 1[.
		 * \return The random number.
		 */
		virtual double randDouble() = 0;
		/**
		 * \brief Generates a random double between [a, b[.
		 * \param a The lower boundary.
		 * \param b The upper boundary.
		 * \return The random number.
		 */
		virtual double randDouble(double a, double b);
		/**
		* \brief Generates a random int between [a, b].
		* \param a The lower boundary.
		* \param b The upper boundary.
		* \return The random number.
		*/
		virtual int randInt(int a, int b);
		/**
		 * \brief Returns the current seed of the random generator.
		 * \return The seed.
		 */
		virtual int getSeed() const;
		/**
		 * \brief Sets a new seed.
		 * \param newSeed The new seed.
		 */
		virtual void setSeed(int newSeed);
	};

}

EMPTY_SERIALIZATION(LightBulb::AbstractRandomGenerator, LightBulb)


#endif