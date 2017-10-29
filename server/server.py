import SocketServer
import User

class MyTCPHandler(SocketServer.BaseRequestHandler):
    """
    The request handler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """

    def handle(self):
        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024)

        print("{} wrote:".format(self.client_address[0]))
        self.reqData = self.data.decode("utf-8");
        self.reqData = self.reqData.split(":", 1)
        business = self.reqData[0]
        self.responseData = ""

        if business == "login":
            self.userData = self.reqData[1].split(",", 1);
            print("Login attempt: {}\t{}".format(self.userData[0], self.userData[1]))
            self.user = User.getUser(self.userData[0])
            if self.user == 0:
                self.responseData("User does not exist")
            else:
                self.user = User.login(self.userData[0], self.userData[1])
                if self.user == 0:
                    self.responseData = "Invalid username or password"
                else:
                    self.responseData = "Successful login"
                    #dodeli neki hash id pa shrani v redis / sql
        elif business == "register":
            self.userData = self.reqData[1].split(",", 1);
            print("Register attempt: {}\t{}".format(self.userData[0], self.userData[1]))
            self.registerResult = User.register(self.userData[0], self.userData[1])
            if self.registerResult == 0:
                    self.responseData = "Username allready taken"
            else:
                    self.responseData = "Successful register"
        else:
            print("Unknown request command {}".format(business))
            self.responseData = "Unknown request"
        # just send back the same data, but upper-cased
        self.request.sendall(self.responseData.encode('utf-8'))

if __name__ == "__main__":
    HOST, PORT = "localhost", 9999

    # Create the server, binding to localhost on port 9999
    server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()