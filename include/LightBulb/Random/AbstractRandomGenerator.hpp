
#pragma once

#ifndef _ABSTRACTRANDOMGENERATOR_H_
#define _ABSTRACTRANDOMGENERATOR_H_

// Include
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

// Library Includes

namespace LightBulb
{
	/**
	 * \brief Describes a generator of random numbers.
	 */
	class AbstractRandomGenerator : public virtual AbstractLinearAlgebraUser
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractRandomGenerator const& randomGenerator);
		template <class Archive>
		friend void load(Archive& archive, AbstractRandomGenerator& randomGenerator);
	private:
	protected:
		Vector<> randomNumberCache;
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
		virtual float randFloat() = 0;
		virtual const Vector<>& randMultipleDouble(int count);
		/**
		 * \brief Generates a random double between [a, b[.
		 * \param a The lower boundary.
		 * \param b The upper boundary.
		 * \return The random number.
		 */
		virtual float randFloat(float a, float b);
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

#include "LightBulb/IO/AbstractRandomGeneratorIO.hpp"


#endif
