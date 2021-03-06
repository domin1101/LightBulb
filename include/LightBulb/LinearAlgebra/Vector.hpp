#pragma once

#ifndef _VECTOR_H_
#define _VECTOR_H_

// Includes
#include <Eigen/Dense>
#include <viennacl/vector.hpp>
#include "AbstractLinearAlgebraObject.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a one dimensional linear algebra data structure, also called vector.
	 * \tparam DataType The data type which should be stored in the data structure.
	 */
	template<typename DataType = float>
	class Vector : public AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, 1>, viennacl::vector<DataType>>
	{
	protected:
		void copyToEigen() const override
		{
			if (this->eigenValue.size() != this->viennaclValue.size())
				this->eigenValue.resize(this->viennaclValue.size());

			viennacl::copy(this->viennaclValue, this->eigenValue);
		}
		void copyToViennaCl() const override
		{
			if (this->eigenValue.size() != this->viennaclValue.size())
				this->viennaclValue.resize(this->eigenValue.size());

			if (this->eigenValue.size() != 0)
				viennacl::copy(this->eigenValue, this->viennaclValue);
		}
	public:
		/**
		* \brief Creates a new matrix with a specific size.
		* \param rows The amount of rows.
		*/
		Vector(int rows = 0)
		{
			if (rows > 0) {
				this->eigenValue = Eigen::Matrix<DataType, -1, 1>(rows);
				this->eigenValueIsDirty = true;
			}
		}
		Vector(const Vector& other)
			: AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, 1>, viennacl::vector<DataType>>()
		{
			if (!((other.eigenValueIsDirty && other.eigenValue.size() == 0) || (other.viennaclValueIsDirty && other.viennaclValue.empty()) || (other.eigenValue.size() == 0 && other.viennaclValue.empty())))
				this->copyAllFrom(other);
		}
		Vector(const Eigen::Matrix<DataType, -1, 1>& eigenVector)
		{
			this->eigenValue = eigenVector;
			this->eigenValueIsDirty = true;
		}
	};
}

#include "LightBulb/IO/VectorIO.hpp"

#endif