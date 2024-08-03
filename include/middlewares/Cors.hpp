#include <crow.h>

// CORS middleware class
class Cors
{
public:
    struct context
    {
    };

    // This function is called before handling the request
    void before_handle(crow::request &req, crow::response &res, context &)
    {
        // If it's an OPTIONS request, return immediately
        if (req.method == "OPTIONS"_method)
        {
            addCorsHeaders(res);
            res.end();
        }
    }

    // This function is called after handling the request
    void after_handle(crow::request & /*req*/, crow::response &res, context &)
    {
        // Add CORS headers to all responses
        addCorsHeaders(res);
    }

private:
    void addCorsHeaders(crow::response &res)
    {
        res.add_header("Access-Control-Allow-Origin", "*");                                // Allow all origins
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS"); // Allow these methods
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");     // Allow these headers
        res.add_header("Access-Control-Allow-Credentials", "true");                        // Allow credentials (cookies, authorization headers, etc.)
    }
};
