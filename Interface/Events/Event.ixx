#include <functional>
#include <unordered_map>

export module Maia.Utilities.Events.Event;

namespace Maia
{
	namespace Utilities
	{
		export template <class OwnerType, class KeyType, class... ParametersTypes>
		class Event
		{
		public:

			// Public definitions:
			using FunctionType = std::function<void(ParametersTypes...)>;
			struct Binding
			{
				KeyType Key;
				FunctionType Function;

				Binding(KeyType key, FunctionType function)
				{
					this->Key = key;
					this->Function = function;
				}

				template<typename TargetType>
				Binding(KeyType key, TargetType* target, void(TargetType::*function)(ParametersTypes...))
				{
					this->Key = key;
					this->Function = [target, function](ParametersTypes... args)
					{
						return (target->*function)(args...);
					};
				}
			};

			// Operator overloads:
			Event& operator +=(const Binding& binding)
			{
				m_bindings.emplace(binding.Key, binding.Function);
				return *this;
			}
			Event& operator -=(KeyType key)
			{
				m_bindings.erase(key);
				return *this;
			}

		private:

			// Friends:
			friend OwnerType;

			// Constructors
			Event() = default;
			Event(const Event& from) = default;
			Event(Event&& from) = default;
			Event& operator=(const Event& from) = default;
			Event& operator=(Event&& from) = default;
			~Event() = default;

			// Operator overloads:
			void operator()(ParametersTypes... arguments) const
			{
				auto localBindingsCopy = m_bindings;
				for (const auto& binding : localBindingsCopy)
				{
					binding.second(arguments...);
				}
			}

			// Members:
			std::unordered_map<KeyType, FunctionType> m_bindings;

		};
	}
}
