//remove in prod
#define LOGGER_ENABLE_AUTO_WRITE 64
#define CONNECTION_TIMEO 300

#include "src/webserver.h" 
#include "src/logging.h"
#include "src/json/json.hpp"
//#include "mousemove.h"

using json = nlohmann::json;

#define mousemove(x, y) system(std::string("xdotool mousemove " + std::to_string(x) + " " + std::to_string(y)).c_str())

int main(int argc, const char **argv) {
	/*
	std::cout << "hello, world\n";
	for (int i = 0; i<500; i++) {
		std::cout << "iteration: " << i <<std::endl;
		//system(std::string("xdotool mousemove " + std::to_string(i + 256) + " " + std::to_string(i + 256)).c_str());
		mousemove(i +  256 * 2, i + 256);
		usleep(1000 * 1);
	}*/


	http::webserver server(
		".",
		1080, 
		512, 
		4);

	server.get("/", [](parsed_request& request, packet_response& response, f_cache &cache) {
		response.set_body_content(cache->fetch("index.html"));
		response.set_content_type("text/html");
		response.set_content_status(200);
	});

	server.get("/style.css", [](parsed_request& request, packet_response& response, f_cache &cache) {
		response.set_body_content(cache->fetch("style.css"));
		response.set_content_type("text/css");
		response.set_content_status(200);
	});

	server.get("/script.js", [](parsed_request& request, packet_response& response, f_cache &cache) {
		response.set_body_content(cache->fetch("script.js"));
		response.set_content_type("application/javascript");
		response.set_content_status(200);
	});

	server.post("/api/cords", [](parsed_request& request, packet_response& response, f_cache &cache) {
		std::cout << "route /api/cords\n";
		
		struct {
			int x;
			int y;
		}pos;

		for (int i = 0; i<2; i++) {
			pos.x = request.body["mouseX"];
			pos.y = request.body["mouseY"];
		}

		std::cout << "mouseX = " << pos.x << std::endl;
		std::cout << "mouseY = " << pos.y << std::endl;

		mousemove(pos.x, pos.y);
		
		
		std::cout << "END FETCH DATA\n";
		
		response.set_body_content (
			" {\"status\": \":)\"}"
		);

		
		response.set_content_type("application/son");
		response.set_content_status(200);
		std::cout << "END ROUTE\n";
	});

	server.run();

	



	return 0;
}