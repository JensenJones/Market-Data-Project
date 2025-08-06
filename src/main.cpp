#include <iostream>

#include "Session.hpp"
#include "WebSocketManager.hpp"
#include "boost/asio/ssl/context.hpp"
#include "example/common/root_certificates.hpp"

std::string urlBase = "wss://data-streamer.coindesk.com/?api_key=$";

int main(int argc, char *argv[]) {
    // Check command line arguments.
    if(argc != 4)
    {
        std::cerr <<
            "Usage: websocket-client-async-ssl <host> <port> <api key>\n" <<
            "Example:\n" <<
            "    websocket-client-async-ssl echo.websocket.org 443 \"123456789JensenIsSexy987654321\"\n";
        return EXIT_FAILURE;
    }
    auto const host = argv[1];
    auto const port = argv[2];
    auto const text = argv[3];

    // The io_context is required for all I/O
    net::io_context ioc;

    // The SSL context is required, and holds certificates
    boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv12_client};

    // Verify the remote server's certificate
    ctx.set_verify_mode(boost::asio::ssl::verify_peer);

    // This holds the root certificate used for verification
    load_root_certificates(ctx);

    // Launch the asynchronous operation
    std::make_shared<Session>(ioc, ctx)->run(host, port, text);

    // Run the I/O service. The call will return when
    // the socket is closed.
    ioc.run();

    return EXIT_SUCCESS;
}
