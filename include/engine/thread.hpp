#ifndef THREAD_HPP_XIAWLCGP
#define THREAD_HPP_XIAWLCGP

namespace rg
{
namespace engine
{
	class thread
	{
		public:
			template<typename Fn, typename... Args>
			thread(Fn&& f, Args&&... args);
			thread(const thread& t) = delete;
			thread(thread&& t) = default;

			void join(void);
		private:
	};
}
}

#endif /* end of include guard: THREAD_HPP_XIAWLCGP */
