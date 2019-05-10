import React, { Component } from 'react';
import './Todo.css';

class Todo extends Component {
  render() {
    return (
    	<div>
	      <div id="01234" class="row todo">
						<p class="blank col-md-3 col-sm-0 col-0"></p>
						<input type="checkbox" name="done" value="Incomplete" class="check col-md-2 col-sm-4 col-4"/>
						<p id="taskName" class="taskName col-md-2 col-sm-4 col-4">Test Task</p>
						<button class="delete col-md-2 col-sm-4 col-4">Delete</button>
						<p class="blank col-md-3 col-sm-0 col-0"></p>
		  </div>
		</div>
    );
  }
}

export default Todo;
