export module Maia.Utilities.Events.InternalEvent;

namespace Maia
{
	namespace Utilities
	{
		export template <class SenderType>
		class InternalEvent
		{
		public:

			// Constructors:
			virtual ~InternalEvent() = default;

			// Public interface:
			virtual void Handle(SenderType& sender) = 0;

		};
	}
}
