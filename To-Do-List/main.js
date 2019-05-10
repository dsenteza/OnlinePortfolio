var apiKey = "7a55e8af7c6ea52e2aa75579cffecf39b8aaad9f76fb3abda368d150ccb450da";

var listReq = new XMLHttpRequest();
listReq.onreadystatechange = function() {
	if(this.readyState == 4 && this.status == 200) {
		var todos = JSON.parse(this.responseText);
		console.log(todos);
		for(var index = 0; index < todos.length; index ++) {
			console.log(todos[index]); 
			renderToDo(todos[index]);
		}
	}
	else if (this.readyState == 4) {
		console.log(this.responseText);
	}
}

listReq.open("GET", "https://api.kraigh.net/todos/", true);
listReq.setRequestHeader("x-api-key", apiKey);
listReq.send();

function addToDo() {
	event.preventDefault();
	var data = {
		text: newTitle.value
	};
	var createReq = new XMLHttpRequest();
	createReq.onreadystatechange = function() {
		// Wait for readyState = 4 & 200 response
	    if (this.readyState == 4 && this.status == 200) {
	        // parse JSON response;
	        renderToDo(JSON.parse(this.responseText));
	    } else if (this.readyState == 4) {
	        // this.status !== 200, error from server
	        console.log(this.responseText);
	    }
	}
	createReq.open("POST", "https://api.kraigh.net/todos", true);
	createReq.setRequestHeader("Content-type", "application/json");
	createReq.setRequestHeader("x-api-key", apiKey);
	createReq.send(JSON.stringify(data));
}

document.getElementById("toDoForm").addEventListener("submit", addToDo);

function renderToDo(todoData) {
	//Todo Container
	var todo = document.createElement("article");
	todo.setAttribute("id", todoData.id);
	todo.classList.add("list");
	if(todoData.completed) {
		todo.classList.add("completed");
	}

	//Space up top
	var breakerog = document.createElement("br");
	todo.appendChild(breakerog);

	//Div for row
	var div = document.createElement("div");
	div.classList.add("row");
	todo.appendChild(div);

	//Breaks betweek
	var breaker = document.createElement("br");
	todo.appendChild(breaker);
	var line = document.createElement("hr");
	todo.appendChild(line);

	//Filler p tag
	var filler = document.createElement("p");
	filler.classList.add("col-0");
	filler.classList.add("col-sm-0");
	filler.classList.add("col-md-3");
	div.appendChild(filler);

	//Checked Complete
	// var complete = document.createElement("button");
	// complete.classList.add("check");
	// complete.classList.add("col-4");
	// complete.classList.add("col-sm-4");
	// complete.classList.add("col-md-2");
	// div.appendChild(complete);
	var complete = document.createElement("input");
	complete.type = "checkbox";
	complete.name = "done";
	complete.classList.add("check");
	complete.classList.add("col-4");
	complete.classList.add("col-sm-4");
	complete.classList.add("col-md-2");
	div.appendChild(complete);

	//Text
	var text = document.createElement("p");
	text.innerText = todoData.text;
	text.classList.add("taskName");
	text.classList.add("col-4");
	text.classList.add("col-sm-4");
	text.classList.add("col-md-2");
	div.appendChild(text);
	console.log(todo);

	//Delete Button
	var del = document.createElement("button");
	del.classList.add("delete");
	del.classList.add("col-4");
	del.classList.add("col-sm-4");
	del.classList.add("col-md-2");
	del.innerText = "Delete";
	div.appendChild(del);

	//Last Filler
	var filler2 = document.createElement("p");
	filler2.classList.add("col-0");
	filler2.classList.add("col-sm-0");
	filler2.classList.add("col-md-3");
	div.appendChild(filler2);

	//Add Todo Element
	document.getElementById("todoApp").appendChild(todo);

	complete.addEventListener("click", completeTodo);
	del.addEventListener("click", deleteTodo);

	document.getElementById("newTitle").value = '';
}

function completeTodo(event) {
	console.log(event);
	var todoId = event.target.parentNode.id;
	var data = {
		completed: true
	};
	var completeReq = new XMLHttpRequest();
	completeReq.onreadystatechange = function() {
		if(this.readyState == 4 && this.status == 200) {
			event.target.parentNode.classList.add("completed");
		}
		else if (this.readyState == 4) {
			console.log(this.responseText);
		}
	}
	completeReq.open("PUT", "https://api.kraigh.net/todos/" + todoId, true);
	completeReq.setRequestHeader("Content-type", "application/json");
	completeReq.setRequestHeader("x-api-key", apiKey);
	completeReq.send(JSON.stringify(data));
}

function deleteTodo(event) {
	var todoId = event.target.parentNode.id;
	var deleteReq = new XMLHttpRequest();
	deleteReq.onreadystatechange = function() {
		if(this.readyState == 4 && this.status == 200) {
			events.target.parentNode.remove();
		}
		else if (this.readyState == 4) {
			console.log(this.responseText);
		}
	}
	deleteReq.open("DELETE", "https://api.kraigh.net/todos/" + todoId, true);
	deleteReq.setRequestHeader("Content-type", "application/json");
	deleteReq.setRequestHeader("x-api-key", apiKey);
	deleteReq.send();
}