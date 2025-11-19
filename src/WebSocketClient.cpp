#include<WebSocketClient.h>

WebSocketClient::WebSocketClient(const std::string& host, const std::string& port, const std::string& path): 
host_(host),
port_(port),
path_(path),
ssl_ctx_(boost::asio::ssl::context::tlsv12_client), 
ws_(ioc_, ssl_ctx_)  
{}

void WebSocketClient::connect()
{
    boost::asio::ip::tcp::resolver resolver(ioc_);
    auto const results = resolver.resolve(host_, port_); //find available endpoints

    boost::asio::connect(ws_.next_layer().next_layer(), results.begin(), results.end()); //TCP connection

    if(! SSL_set_tlsext_host_name(ws_.next_layer().native_handle(), host_.c_str()))
    {
        throw boost::system::system_error(
            boost::asio::error::operation_not_supported,
            "SNI Hostname Set Failed"
        );
    }

    ws_.next_layer().handshake(boost::asio::ssl::stream_base::client); //SSL handshake
    ws_.handshake(host_ + ":" + port_, path_); //Web Socket handshake

    ws_.control_callback(
    [&](boost::beast::websocket::frame_type frame_type,
        boost::beast::string_view payload)
    {
        if(frame_type == boost::beast::websocket::frame_type::ping)
        {
            ws_.pong(boost::beast::websocket::ping_data{payload.data(), payload.size()});
        }
    });
}

void WebSocketClient::run()
{

}