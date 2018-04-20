import std.threading;

export module Maia.Utilities.Threading.Task;

namespace Maia
{
	namespace Utilities
	{
		export class Task
		{
		public:

			// Constructors:
			template<typename FunctionType>
			explicit Task(FunctionType&& function) :
				m_ready(false)
			{
				std::packaged_task<void()> task(std::forward<FunctionType>(function));
				m_future = task.get_future();
				m_thread = std::thread(std::move(task));
			}

			void Update()
			{
				if(m_ready)
				{
					if (m_future.valid() && m_future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
					{
						m_ready = true;
					}
				}
			}

			bool IsReady() const noexcept
			{
				return m_ready;
			}

			void Join()
			{
				if (m_thread.joinable())
					m_thread.join();
			}

		private:
		
			// Members:
			std::future<void> m_future;
			std::thread m_thread;
			bool m_ready;

		};
	}
}
