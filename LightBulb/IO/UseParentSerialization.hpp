#pragma once

#ifndef _USEPARENTSERIALIZATION_H_
#define _USEPARENTSERIALIZATION_H_

// Includes

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>

#include "IO/UsedArchives.hpp"

#define USE_PARENT_SERIALIZATION(T, Parent) \
template <class Archive> \
void save(Archive& archive, T const& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
template <class Archive> \
void load(Archive& archive, T& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
CEREAL_REGISTER_TYPE(T);

#define EMPTY_CHILD_SERIALIZATION(T) \
template <class Archive> \
void save(Archive& archive, T const& trainingPlan) \
{ \
} \
template <class Archive> \
void load(Archive& archive, T& trainingPlan) \
{ \
} \
CEREAL_REGISTER_TYPE(T);

#define EMPTY_SERIALIZATION(T) \
template <class Archive> \
void save(Archive& archive, T const& trainingPlan) \
{ \
} \
template <class Archive> \
void load(Archive& archive, T& trainingPlan) \
{ \
} \

#endif