// Require the packages we will use:
var http = require("http"),
	socketio = require("socket.io"),
	fs = require("fs");

// Listen for HTTP connections
var app = http.createServer(function(req, resp){
	fs.readFile("client.html", function(err, data){
		if(err) return resp.writeHead(500);
		resp.writeHead(200);
		resp.end(data);
	});
});
app.listen(3456);

var socketIo = socketio.listen(app);
var usernames = [];
var room;

//Referenced: https://stackoverflow.com/questions/1181575/determine-whether-an-array-contains-a-value
//Method taken from above link - supports printing users to check if array of displayed users 'usersInRoom' contains the name
var contains = function(needle) {
  //Identify NaN by checking if it is not equal to itself
  var findNaN = needle !== needle;
  var indexOf;
  if(!findNaN && typeof Array.prototype.indexOf === "function") {
      indexOf = Array.prototype.indexOf;
  } else {
      indexOf = function(needle) {
          var i = -1, index = -1;
          for(i = 0; i < this.length; i++) {
              var item = this[i];

              if((findNaN && item !== item) || item === needle) {
                  index = i;
                  break;
              }
          }
          return index;
      };
  }
  return indexOf.call(this, needle) > -1;
};

socketIo.sockets.on("connection", function(socket) {
	//Auto joins the default room
	socket.on("autoJoin", function(room) {
		socket.leave(socket.room);
		socket.join("default_room");
		socket.room = room;
	});

	//Sends messages including the nickname back to client.
	socket.on("to_server", function(data) {
		socketIo.sockets.in(socket.room).emit("to_client", {message:data["message"]});
		socketIo.sockets.in(socket.room).emit("user2client", {nickname:data["nickname"]});
		var index = contains.call(usernames, data["nickname"]);
        if (!index) {
			usernames[usernames.length] = data["nickname"];
		}
	});

	//Switching rooms referenced: http://psitsmike.com/2011/10/node-js-and-socket-io-multiroom-chat-tutorial/
	socket.on("switchRooms", function(room) {
		socket.leave(socket.room);
		socket.join(room);
		socket.room = room;
		socket.emit("updateRoom",{room:room});
	});	
});