// extent client interface.

#ifndef extent_client_h
#define extent_client_h

#include <string>
#include "extent_protocol.h"
#include "extent_server.h"

#ifndef USE_EXTENT_CACHE  
class extent_client
{
private:
  rpcc *cl;

public:
  extent_client(std::string dst);

  extent_protocol::status create(uint32_t type, extent_protocol::extentid_t &eid);
  extent_protocol::status get(extent_protocol::extentid_t eid,
                              std::string &buf);
  extent_protocol::status getattr(extent_protocol::extentid_t eid,
                                  extent_protocol::attr &a);
  extent_protocol::status put(extent_protocol::extentid_t eid, std::string buf);
  extent_protocol::status remove(extent_protocol::extentid_t eid);
};
#else
class extent_client
{
private:
  rpcc *cl;
  int rextent_port;
  std::string hostname;
  std::string id;

  struct fileinfo {
    bool attr_valid;
    bool buf_valid;
    bool writable;
    extent_protocol::attr attr;
    std::string buf;
    std::list<pthread_cond_t *> thread_list;

    fileinfo() {
      attr_valid = false;
      buf_valid = false;
      writable = false;
      attr.size = 0;
      attr.type = 0;
      attr.atime = time(NULL);
      attr.mtime = time(NULL);
      attr.ctime = time(NULL);
      buf.clear();
    }
  };

  pthread_mutex_t extentmutex;
  std::map<extent_protocol::extentid_t, fileinfo *> filemap;

public:
  static int last_port;
  extent_client(std::string dst);
  ~extent_client();
  extent_protocol::status create(uint32_t type, extent_protocol::extentid_t &eid);
  extent_protocol::status get(extent_protocol::extentid_t eid,
                              std::string &buf);
  extent_protocol::status getattr(extent_protocol::extentid_t eid,
                                  extent_protocol::attr &a);
  extent_protocol::status put(extent_protocol::extentid_t eid, std::string buf);
  extent_protocol::status remove(extent_protocol::extentid_t eid);

  extent_protocol::status pull_handler(extent_protocol::extentid_t eid, int &);
  extent_protocol::status push_handler(extent_protocol::extentid_t eid, int &);

};

#endif
#endif