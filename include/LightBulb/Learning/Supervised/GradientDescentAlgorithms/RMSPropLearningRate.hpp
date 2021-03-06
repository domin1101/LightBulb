#pragma once

#ifndef _RMSPROPLEARNINGRATEHELPEROPTIONS_H_
#define _RMSPROPLEARNINGRATEHELPEROPTIONS_H_

// Library Includes
#include <vector>

// Includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"

namespace LightBulb
{
	class Kernel;
	/**
	* \brief All options for the RMSprop learning rate.
	*/
	struct RMSPropLearningRateOptions : public AbstractGradientDescentAlgorithmOptions
	{
		/**
		 * \brief The momentum of the gradient.
		 * \details Default value: 0.95
		 */
		double gradientMomentum;
		/**
		 * \brief The momentum of the squared gradient.
		 * \details Default value: 0.95
		 */
		double squaredGradientMomentum;
		/**
		 * \brief The momentum of the calculated delta weights.
		 * \details Default value: 0.9
		 */
		double deltaWeightsMomentum;
		/**
		 * \brief The learning rate.
		 * \details Default value: 0.25
		 */
		double learningRate;
		/**
		 * \brief The basic squared gradient.
		 * \details Default value: 0.01
		 */
		double minSquaredGradient;
		/**
		 * \brief Creates the options and fills them with default options.
		 */
		RMSPropLearningRateOptions()
		{
			gradientMomentum = 0.95;
			squaredGradientMomentum = 0.95;
			deltaWeightsMomentum = 0.9;
			learningRate = 0.25;
			minSquaredGradient = 0.01;
		}
		AbstractCloneable* clone() const override
		{
			return new RMSPropLearningRateOptions(*this);
		}
	};


	/**
	 * \brief Performs a normalized gradient descent step.
	 * \details  \f$s_t = (1 - \alpha)~f'(\omega_t) + \alpha s_{t-1}\f$ \n \n
	 * \f$r_t = (1 - \gamma)~f'(\omega_t)^2 + \gamma r_{t-1}\f$ \n \n
	 * \f$\Delta\omega_{t+1} = \beta \Delta\omega_{t} + (1 - \beta) \eta {f'(\omega_t) \over \sqrt{r_t - s_t + \delta}}\f$ \n \n
	 * \f$\alpha: gradientMomentum\f$ \n 
	 * \f$\gamma: squaredGradientMomentum\f$ \n 
	 * \f$\beta: deltaWeightsMomentum\f$ \n 
	 * \f$\delta: minSquaredGradient\f$ \n
	 * \f$\eta: learningRate\f$ 
	 */
	class RMSPropLearningRate : public AbstractGradientDescentAlgorithm
	{
		template <class Archive>
		friend void serialize(Archive& archive, RMSPropLearningRate& rmsPropLearningRate);
		friend struct cereal::LoadAndConstruct<RMSPropLearningRate>;
	private:
		std::unique_ptr<Kernel> rmsPropLearningRateKernel;
		/**
		 * \brief Remembers the previous gradient
		 */
		std::vector<Matrix<>> prevGradient;
		/**
		* \brief Remembers the previous squared gradient
		*/
		std::vector<Matrix<>> prevSquaredGradient;
		/**
		* \brief Remembers the previous delta weights
		*/
		std::vector<Matrix<>> prevDeltaWeights;
		/**
		* \brief Returns our current options in form of a RMSPropLearningRateOptions object.
		* \return The RMSPropLearningRateOptions object.
		*/
		RMSPropLearningRateOptions& getOptions();
	public:
		/**
		* \brief Creates the RMSprop learning rate.
		* \param options_ The options which configure the RMSprop learning rate.
		*/
		RMSPropLearningRate(const RMSPropLearningRateOptions& options_);
		/**
		 * \brief Creates the RMSprop learning rate with default options.
		 */
		RMSPropLearningRate();
		~RMSPropLearningRate();
		RMSPropLearningRate(RMSPropLearningRate&& other) noexcept;
		RMSPropLearningRate(const RMSPropLearningRate& other) = default;
		RMSPropLearningRate& operator=(RMSPropLearningRate other);

		friend void swap(RMSPropLearningRate& lhs, RMSPropLearningRate& rhs) noexcept;

		// Inherited:
		void adjustWeights(const AbstractNetworkTopology& networkTopology, Matrix<>& weights, int layerIndex, const Matrix<>& gradients) override;
		bool learningHasStopped() override;
		void initializeAlgorithm(const AbstractNetworkTopology& networkTopology) override;
		AbstractCloneable* clone() const override;
	};
}

#include "LightBulb/IO/RMSPropLearningRateIO.hpp"

#endif

