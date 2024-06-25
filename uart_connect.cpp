#include "uart_connect.h"

void gps(GPS &gps_data) {
    try {
        boost::asio::io_service io;
        boost::asio::serial_port serial(io, "/dev/ttyS1");

        serial.set_option(boost::asio::serial_port_base::baud_rate(115200));
        serial.set_option(boost::asio::serial_port_base::character_size(8));
        serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
        serial.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

        std::string buf[256];

        while (true) {
            try{
                boost::system::error_code error;
                size_t len = serial.read_some(boost::asio::buffer(buf), error);
                parser(line, gps_data);
            } catch(...){
                continue;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}
