#include "engine/id.hpp"

namespace rg
{
namespace engine
{


namespace uuids
{
	static boost::uuids::random_generator ran_gen;		
	static boost::uuids::uuid uuid_namespace;
	static boost::uuids::name_generator name_gen(uuid_namespace);

	const uuid null_id(boost::uuids::nil_uuid());

	uuid random_id(void)
	{
		return ran_gen();
	}

	uuid name_id(const std::string& name)
	{
		return name_gen(name);
	}

	bool is_null(const uuid& id)
	{
		return id.is_nil() == true;
	}
}
}
}
