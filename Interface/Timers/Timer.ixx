import std.core;
import std.threading;

export module Maia.Utilities.Timers;

namespace Maia
{
	namespace Utilities
	{
		export class Timer
		{
		public:

			// Public definitions:
			using ClockType = std::chrono::high_resolution_clock;
			using TimePointType = ClockType::time_point;
			using DurationType = ClockType::duration;

			// Constructors:
			Timer() :
				m_timePerUpdate(std::chrono::microseconds(12)),
				m_deltaTime(ClockType::duration(0))
			{
			}
			explicit Timer(DurationType timePerUpdate) :
				m_timePerUpdate(timePerUpdate),
				m_deltaTime(ClockType::duration(0))
			{
			}

			void Reset()
			{
				std::unique_lock<std::shared_mutex> lock(m_mutex);

				m_previousTimePoint = ClockType::now();
				m_lag = DurationType::zero();
			}
			void Update()
			{
				std::unique_lock<std::shared_mutex> lock(m_mutex);

				m_currentTimePoint = ClockType::now();

				m_deltaTime = m_currentTimePoint - m_previousTimePoint;
				m_previousTimePoint = m_currentTimePoint;
				m_totalTime += m_deltaTime;

				m_lag += m_deltaTime;
			}
			void RunFixedUpdate(const std::function<void(const Timer&)>& fixedUpdate)
			{
				std::size_t updateCount;

				{
					std::shared_lock<std::shared_mutex> lock(m_mutex);

					if (m_lag < m_timePerUpdate)
						return;

					updateCount = static_cast<std::size_t>(m_lag / m_timePerUpdate);
				}

				// Update the times needed to catchup:
				for (std::size_t i = 0; i < updateCount; ++i)
				{
					fixedUpdate(*this);
				}

				{
					std::unique_lock<std::shared_mutex> lock(m_mutex);
					m_lag -= m_timePerUpdate * updateCount;
				}
			}

			template <typename FixedUpdateFunctionType, typename FrameUpdateFunctionType, typename RenderFunctionType, typename ProcessInputFunctionType, typename ProcessFrameStatisticsFunctionType>
			bool UpdateAndRender(FixedUpdateFunctionType&& fixedUpdate, FrameUpdateFunctionType&& frameUpdate, RenderFunctionType&& render, ProcessInputFunctionType&& processInput, ProcessFrameStatisticsFunctionType&& processFrameStatistics)
			{
				Update();

				// Process input:
				processInput();

				// Update the times needed to catchup:
				while (m_lag >= m_timePerUpdate)
				{
					fixedUpdate(*this);
					m_lag -= m_timePerUpdate;
				}

				// Render:
				if (!frameUpdate(*this))
					return false;
				render(*this);

				// Calculate frames statistics (frames per second, milliseconds per frame):
				CalculateFrameStatistics(processFrameStatistics);

				return true;
			}

			// Getters:
			DurationType GetTimePerUpdate() const
			{
				std::shared_lock<std::shared_mutex> lock(m_mutex);
				return m_timePerUpdate;
			}
			DurationType GetTotalTime() const
			{
				std::shared_lock<std::shared_mutex> lock(m_mutex);
				return m_totalTime;
			}
			DurationType GetDeltaTime() const
			{
				std::shared_lock<std::shared_mutex> lock(m_mutex);
				return m_deltaTime;
			}
			double GetLeftover() const
			{
				std::shared_lock<std::shared_mutex> lock(m_mutex);
				return std::chrono::duration<double>(m_lag) / std::chrono::duration<double>(m_timePerUpdate);
			}
			size_t GetFramesPerSecond() const
			{
				std::shared_lock<std::shared_mutex> lock(m_mutex);
				return m_framesPerSecond;
			}
			DurationType GetTimePerFrame() const
			{
				std::shared_lock<std::shared_mutex> lock(m_mutex);
				return m_timePerFrame;
			}

			// Setters:
			void SetTotalTime(DurationType totalTime)
			{
				std::unique_lock<std::shared_mutex> lock(m_mutex);
				m_totalTime = totalTime;
			}
			void SetDeltaTime(DurationType deltaTime)
			{
				std::unique_lock<std::shared_mutex> lock(m_mutex);
				m_deltaTime = deltaTime;
			}

		private:

			// Auxiliary methods:
			template<typename ProcessFrameStatisticsFunctionType>
			void CalculateFrameStatistics(ProcessFrameStatisticsFunctionType&& processFrameStatistics)
			{
				static auto elapsedTime = DurationType::zero();
				static size_t frameCount = 0;

				// Increment frame count:
				++frameCount;

				// If one second has elapsed:
				if (m_totalTime - elapsedTime >= std::chrono::seconds(1))
				{
					// Update values:
					m_framesPerSecond = frameCount;
					m_timePerFrame = std::chrono::seconds(1) / static_cast<std::chrono::seconds::rep>(frameCount);

					// Reset frame count and increment elapsed time by 1 second:
					frameCount = 0;
					elapsedTime += std::chrono::seconds(1);

					processFrameStatistics(*this);
				}
			}

		private:

			const DurationType m_timePerUpdate;

			DurationType m_totalTime;
			DurationType m_deltaTime;
			DurationType m_lag;

			TimePointType m_currentTimePoint;
			TimePointType m_previousTimePoint;

			size_t m_framesPerSecond = 0;
			DurationType m_timePerFrame;

			mutable std::shared_mutex m_mutex;
		};
	}
}