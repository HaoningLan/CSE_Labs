#include "ydb_server.h"
#include "extent_client.h"

//#define DEBUG 1

static long timestamp(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

ydb_server::ydb_server(std::string extent_dst, std::string lock_dst)
{
	ec = new extent_client(extent_dst);
	lc = new lock_client(lock_dst);
	//lc = new lock_client_cache(lock_dst);

	long starttime = timestamp();

	for (int i = 2; i < 1024; i++)
	{ // for simplicity, just pre alloc all the needed inodes
		extent_protocol::extentid_t id;
		ec->create(extent_protocol::T_FILE, id);
		printf("%llu\n", id);
	}

	long endtime = timestamp();
	printf("time %ld ms\n", endtime - starttime);
}

ydb_server::~ydb_server()
{
	delete lc;
	delete ec;
}

extent_protocol::extentid_t ydb_server::key2id(const std::string key)
{
	unsigned int seed = 131;
	extent_protocol::extentid_t hash = 0;
	for (unsigned int i = 0; i < key.length(); i++)
	{
		hash = hash * seed + key[i];
	}
	return (hash % 1022) + 2;
}

ydb_protocol::status ydb_server::transaction_begin(int, ydb_protocol::transaction_id &out_id)
{ // the first arg is not used, it is just a hack to the rpc lib
	// no imply, just return OK
	return ydb_protocol::OK;
}

ydb_protocol::status ydb_server::transaction_commit(ydb_protocol::transaction_id id, int &)
{
	// no imply, just return OK
	return ydb_protocol::OK;
}

ydb_protocol::status ydb_server::transaction_abort(ydb_protocol::transaction_id id, int &)
{
	// no imply, just return OK
	return ydb_protocol::OK;
}

ydb_protocol::status ydb_server::get(ydb_protocol::transaction_id id, const std::string key, std::string &out_value)
{
	// lab3: your code here

	extent_protocol::extentid_t ex_id = key2id(key);
	ec->get(ex_id, out_value);
	return ydb_protocol::OK;
}

ydb_protocol::status ydb_server::set(ydb_protocol::transaction_id id, const std::string key, const std::string value, int &)
{
	// lab3: your code here

	extent_protocol::extentid_t ex_id = key2id(key);
	ec->put(ex_id, value);
	return ydb_protocol::OK;
}

ydb_protocol::status ydb_server::del(ydb_protocol::transaction_id id, const std::string key, int &)
{
	// lab3: your code here

	extent_protocol::extentid_t ex_id = key2id(key);
	ec->put(ex_id, "");
	return ydb_protocol::OK;
}
