#ifndef _NAVAGRAHA_HTTP_CLIENT_CLIENT_H
#define _NAVAGRAHA_HTTP_CLIENT_CLIENT_H

#include <curl/curl.h>
#include <sstream>
#include <string>
#include <functional>

namespace navagraha {
namespace http_client {

class client {
private:
    CURL * curl;
    const std::string host;
    std::string payload;
    std::string result;
    std::string content_type;
    const char * binary_payload;
    size_t binary_payload_length;
    std::function<void (std::string &)> receive_cb;

    std::string uri(const std::string path) const;

protected:
    std::string & curl_abstract_process(const std::string path, const char * method);

    template <typename T> T get_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "GET"));
    }

    template <typename T> T put_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "PUT"));
    }

    template <typename T> T delete_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "DELETE"));
    }

    template <typename T> T post_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "POST"));
    }

    template <typename T> T patch_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "PATCH"));
    }

    template <typename T> void set_payload(T && obj)
    {
        std::ostringstream str;
        obj.serialize(str);
        this->payload = str.str();
    }

    void set_binary_content(std::string & val);

public:
    client(CURL * curl, const std::string host);

    virtual ~client();

    size_t write(const char * ptr, size_t size);

    client & set_content_type(std::string content_type);

    client & set_receive_cb(std::function<void (std::string &)> cb);
};

}
}

#endif
