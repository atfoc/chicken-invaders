#ifndef ID_HPP_UGSNADMC
#define ID_HPP_UGSNADMC

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace rg
{
namespace engine
{

using uuid = boost::uuids::uuid;

namespace uuids
{

	extern const uuid null_id;

	uuid random_id(void);
	uuid name_id(const std::string& name); 
	bool is_null(const uuid& id);
}
}
}

#endif /* end of include guard: ID_HPP_UGSNADMC */
