#include <string>
#include <set>

namespace netlib {

	class network {
		network(const network&);
		network& operator=(const network&);
	public:
		static char* create_packet(const size_t size);
		network();
		virtual ~network();
		virtual bool send_packet(const char* packet, const size_t size) = 0;
		virtual const char* const get_packet(size_t* const size) = 0;
		virtual void validate(const std::string& name) const = 0;
	};

	class net_protocol {
	public:
		explicit net_protocol(network& n);
		void connect(const std::string& password);
		void heartbeat();
		void validate(const std::string& name);
		bool is_in_local_cache(const std::string& ) const;
	private:
		network& _n;
		std::set<std::string> _validated_local_cache;
	};
}
