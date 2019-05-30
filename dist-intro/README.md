
# Distributed Systems: Introduction

A simple UDP client and server:
- `client.c`: example client code, sends a message to the server and waits for a reply
- `server.c`: example server code, waits for messages indefinitely and replies

Both use `udp.c` as a simple UDP communication library.

The `Makefile` builds `client` and `server` executables. Type `make` to do this.

To run: type `server &` to run the server in the background; then type `client` to
run the client. You will likely then want to kill the server if you are done.

If you want to run these on different machines, you'll have to change the client
to send messages to the machine the server is running upon, instead of `localhost`.

