#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

// Includes
#include <Eigen/Dense>
#include <viennacl/matrix.hpp>
#include "AbstractLinearAlgebraObject.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a two dimensional linear algebra data structure, also called matrix.
	 * \note Red or blue?
	 * \tparam DataType The data type which should be stored in the data structure.
	 */
	template<typename DataType = float>
	class Matrix : public AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, -1>, viennacl::matrix<DataType>>
	{
	protected:
		// Inherited:
		void copyToEigen() const override
		{
			if (this->eigenValue.rows() != this->viennaclValue.size1() || this->eigenValue.cols() != this->viennaclValue.size2())
				this->eigenValue.resize(this->viennaclValue.size1(), this->viennaclValue.size2());

			viennacl::copy(this->viennaclValue, this->eigenValue);
		}
		void copyToViennaCl() const override
		{
			if (this->eigenValue.rows() != this->viennaclValue.size1() || this->eigenValue.cols() != this->viennaclValue.size2())
				this->viennaclValue.resize(this->eigenValue.rows(), this->eigenValue.cols());

			if (this->eigenValue.size() != 0)
				viennacl::copy(this->eigenValue, this->viennaclValue);
		}
	public:
		/**
		 * \brief Creates a new matrix with a specific size.
		 * \param rows The amount of rows.
		 * \param cols The amount of cols.
		 */
		Matrix(int rows = 0, int cols = 0)
		{
			if (rows > 0 && cols > 0) {
				this->eigenValue = Eigen::Matrix<DataType, -1, -1>(rows, cols);
				this->eigenValueIsDirty = true;
			}
		}
		Matrix(const Eigen::Matrix<DataType, -1, -1>& eigenMatrix)
		{
			this->eigenValue = eigenMatrix;
			this->eigenValueIsDirty = true;
		}
		Matrix(const Matrix& other)
			: AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, -1>, viennacl::matrix<DataType>>()
		{
			if (!((other.eigenValueIsDirty && other.eigenValue.size() == 0) || (other.viennaclValueIsDirty && other.viennaclValue.size1() == 0 && other.viennaclValue.size2() == 0) || (other.eigenValue.size() == 0 && other.viennaclValue.size1() == 0 && other.viennaclValue.size2() == 0)))
				this->copyAllFrom(other);
		}
	};

}


#include "LightBulb/IO/MatrixIO.hpp"

#endif