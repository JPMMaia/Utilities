export module Maia.Utilities.Exceptions;

import std.core;

namespace Maia
{
	namespace Utilities
	{
		export class EngineException : public std::exception
		{
		public:

			// Constructors:
			EngineException() = default;
			explicit EngineException(const std::string& message) :
				m_message(message)
			{
			}

			// std::exception overrides:
			const char* what() const noexcept override
			{
				return m_message.c_str();
			}

		private:

			// Members:
			std::string m_message;

		};
	}
}
