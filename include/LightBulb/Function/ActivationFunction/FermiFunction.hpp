#pragma once

#ifndef _FERMIFUNCTION_H_
#define _FERMIFUNCTION_H_

// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include <viennacl/vector.hpp>

namespace viennacl
{
	struct op_fermi {};
	namespace linalg
	{
		namespace detail
		{
			template<>
			struct op_applier<viennacl::op_element_unary<op_fermi>>
			{
				template<typename T>
				static void apply(T & result, T const & x) { using namespace std; result = x; }
			};
		}

		namespace opencl
		{
			namespace detail
			{
				inline std::string op_to_string(op_fermi) { return "fermi"; }
			}
		}
	}
}

namespace LightBulb
{
	

	/**
	 * \brief The FermiFunction is a sigmoid function between 0 and 1 which can be adjusted with temperatureParameter.
	 * \details Describes: \n \n \f$ f(x) = \frac{1}{1 + e^{\frac{-x}{\beta}}} \f$ \n \n
	 * Derivative: \n \n \f$ f'(x) = f(x) * (1 - f(x)) \f$
	 */
	class FermiFunction : public AbstractActivationFunction
	{
		template <class Archive>
		friend void serialize(Archive& archive, FermiFunction& fermiFunction);
	private:
		/**
		 * \brief The temperature parameter which describes how fast the function raises
		 */
		double temperatureParameter;
	public:
		/**
		 * \brief Creates a FermiFunction
		 * \param temperatureParameter_ The temperature parameter which describes how fast the function raises
		 */
		FermiFunction(double temperatureParameter_ = 1);
		// Inherited
		double execute(double input) const override;
		double executeDerivation(double input) const override;
		AbstractCloneable* clone() const override;
		double getMaximum() const override;
		double getMinimum() const override;
		bool hasAMaxAndMinimum() const override;
		void execute(int layerNr, std::vector<Vector<>>& activations, const std::vector<Vector<>>& netInputs) const override;
		void executeDerivation(const Vector<>& input, Vector<>& derivation) const override;
	};
}

#include "LightBulb/IO/FermiFunctionIO.hpp"

#endif