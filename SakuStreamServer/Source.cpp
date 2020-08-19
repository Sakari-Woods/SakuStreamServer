#include <iostream>
#include <stdio.h>
#include <enet/enet.h>
#include <string>

ENetAddress address;
ENetHost * server;
ENetPeer *peer;
bool quit = false;

void startServer() {

	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	enet_address_set_host (& address, "127.0.0.1");
	address.host = ENET_HOST_ANY;
	/* Bind the server to port 1234. */
	address.port = 1234;
	server = enet_host_create(&address /* the address to bind the server host to */,
		32      /* allow up to 32 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
}

void shutdownServer() {
	enet_host_destroy(server);
	printf("Server shut down and released.");
}

void startListening() {
	ENetEvent event;
	// Refreshes once every 10 seconds.
		while (enet_host_service(server, &event, 0) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("Connected.");
				printf("A new client connected from %x:%u.\n",
					event.peer->address.host,
					event.peer->address.port);
				break;

			case ENET_EVENT_TYPE_RECEIVE:
				printf("Packet received.");
				printf("(Client) Message from server : %s\n", event.packet->data);
				enet_packet_destroy(event.packet);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("Disconnected.");
				printf("%s disconnected.\n", event.peer->data);
				//puts("Disconnection succeeded.");
				//return;
				break;

			case ENET_EVENT_TYPE_NONE:
				printf("Nothing happened.");
				break;
			}
	}
}

int main(int argc, char** argv) {
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	printf("Starting server...");
	startServer();
	while (!quit) {
		startListening();
	}
	
	printf("Enter anything to exit.");
	system("pause");
	shutdownServer();
	std::cin.get();
	return 0;
}