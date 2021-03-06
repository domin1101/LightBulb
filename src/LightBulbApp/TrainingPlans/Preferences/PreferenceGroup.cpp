﻿// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/ChoicePreference.hpp"

namespace LightBulb
{
	PreferenceGroup::PreferenceGroup(const std::string& name_)
	{
		name = name_;
	}

	PreferenceGroup::PreferenceGroup(const PreferenceGroup& other)
		:AbstractPreferenceElement(other)
	{
		name = other.name;
		preferences.clear();
		for (auto preference = other.preferences.begin(); preference != other.preferences.end(); preference++)
		{
			addPreference(dynamic_cast<AbstractPreferenceElement*>((*preference)->clone()));
		}
	}

	PreferenceGroup::PreferenceGroup(PreferenceGroup&& other) noexcept
		:PreferenceGroup()
	{
		swap(*this, other);
	}

	PreferenceGroup& PreferenceGroup::operator=(PreferenceGroup other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(PreferenceGroup& lhs, PreferenceGroup& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractPreferenceElement&>(lhs), static_cast<AbstractPreferenceElement&>(rhs));
		swap(lhs.name, rhs.name);
		swap(lhs.preferences, rhs.preferences);
	}

	const std::string& PreferenceGroup::getName() const
	{
		return name;
	}

	std::string PreferenceGroup::toString(std::string offset) const
	{
		std::string text = name + ":\n";
		for (auto preference = preferences.begin(); preference !=preferences.end(); preference++)
		{
			text += offset + " - " + (*preference)->toString(offset + "  ");
		}
		return text;
	}

	void PreferenceGroup::setName(std::string newName)
	{
		name = newName;
	}

	void PreferenceGroup::addPreference(AbstractPreferenceElement* preferenceElement)
	{
		preferences.push_back(std::unique_ptr<AbstractPreferenceElement>(preferenceElement));
	}

	AbstractCloneable* PreferenceGroup::clone() const
	{
		return new PreferenceGroup(*this);
	}

	const AbstractPreference& PreferenceGroup::getPreference(const std::string& preferenceName) const
	{
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			if (dynamic_cast<AbstractPreference*>(preference->get()) && (*preference)->getName() == preferenceName)
				return static_cast<AbstractPreference&>(*preference->get());
		}
		throw std::invalid_argument("There is no preference with name \"" + preferenceName + "\"");
	}

	PreferenceGroup& PreferenceGroup::getPreferenceGroup(const std::string& preferenceGroupName) const
	{
		for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
		{
			if (dynamic_cast<PreferenceGroup*>(preference->get()) && (*preference)->getName() == preferenceGroupName)
				return static_cast<PreferenceGroup&>(*preference->get());
		}
		throw std::invalid_argument("There is no preference group with name \"" + preferenceGroupName + "\"");
	}

	double PreferenceGroup::getDoublePreference(const std::string& preferenceName) const
	{
		const DoublePreference* doublePreference = dynamic_cast<const DoublePreference*>(&getPreference(preferenceName));
		if (doublePreference)
			return doublePreference->getValue();
		else
			return 0;
	}


	int PreferenceGroup::getIntegerPreference(const std::string& preferenceName) const
	{
		const IntegerPreference* integerPreference = dynamic_cast<const IntegerPreference*>(&getPreference(preferenceName));
		if (integerPreference)
			return integerPreference->getValue();
		else
			return 0;
	}

	bool PreferenceGroup::getBooleanPreference(const std::string& preferenceName) const
	{
		const BooleanPreference* booleanPreference = dynamic_cast<const BooleanPreference*>(&getPreference(preferenceName));
		if (booleanPreference)
			return booleanPreference->getValue();
		else
			return false;
	}

	std::string PreferenceGroup::getChoicePreference(const std::string& preferenceName) const
	{
		const ChoicePreference* choicePreference = dynamic_cast<const ChoicePreference*>(&getPreference(preferenceName));
		if (choicePreference)
			return choicePreference->getValue();
		else
			return "";
	}

	const std::vector<std::unique_ptr<AbstractPreferenceElement>>& PreferenceGroup::getPreferenceElements() const
	{
		return preferences;
	}

}
